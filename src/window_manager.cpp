#include "window_manager.h"

#include <stdexcept>

WindowManager::WindowManager(const int width, const int height, const char* title, const WindowCallbackInfo info)
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
    if (info.frameBufferSizeCallback)
        glfwSetFramebufferSizeCallback(_window, *info.frameBufferSizeCallback);
    if (info.mouseCallback)
        glfwSetCursorPosCallback(_window, *info.mouseCallback);
    if (info.scrollCallback)
        glfwSetScrollCallback(_window, *info.scrollCallback);
    if (info.inputCallback)
        _inputCallBack = *info.inputCallback;
    if (info.loopCallback)
        _loopCallBack = *info.loopCallback;

    // tell GLFW to capture our mouse
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
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

void WindowManager::changeViewport(const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void WindowManager::render()
{
    while (!glfwWindowShouldClose(_window))
    {
        const auto currentTime = static_cast<float>(glfwGetTime());
        _deltaTime = currentTime - _lastTime;
        _lastTime = currentTime;

        _inputCallBack(_window, _deltaTime);
        _loopCallBack(_window, _deltaTime);

        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, true);

        glfwPollEvents();
        glfwSwapBuffers(_window);
    }
    glfwTerminate();
}
