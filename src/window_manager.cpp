#include "window_manager.h"

#include <stdexcept>


void framebuffer_size_callback(GLFWwindow* _,
                               const int width, const int height)
{
    glViewport(0, 0, width, height);
}

WindowManager::WindowManager(const int width, const int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

WindowManager::~WindowManager()
{
    glfwMakeContextCurrent(nullptr);

    if (_window != nullptr)
    {
        glfwTerminate();
        _window = nullptr;
    }
}

void WindowManager::setLoopCallback(const std::function<void(GLFWwindow*)>& callback)
{
    _loopCallBack = callback;
}

void WindowManager::setClearColor(const float r, const float g, const float b, const float a)
{
    glClearColor(r, g, b, a);
}

void WindowManager::clearBuffer(const bool color, const bool depth, const bool stencil)
{
    auto mask = 0;
    if (color)
        mask |= GL_COLOR_BUFFER_BIT;
    if (depth)
        mask |= GL_DEPTH_BUFFER_BIT;
    if (stencil)
        mask |= GL_STENCIL_BUFFER_BIT;
    glClear(mask);
}

void WindowManager::setDrawLine()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void WindowManager::enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
}

void WindowManager::render() const
{
    while (!glfwWindowShouldClose(_window))
    {
        _loopCallBack(_window);

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, true);

        glfwPollEvents();
        glfwSwapBuffers(_window);
    }
    glfwTerminate();
}
