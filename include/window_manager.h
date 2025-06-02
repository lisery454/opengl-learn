#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <functional>
#include <utility>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class WindowManager
{
public:
    WindowManager(int width, int height, const char* title);
    ~WindowManager();

    void update();

    static void setClearColor(float r, float g, float b, float a);
    static void clearBuffer(bool color = false, bool depth = false, bool stencil = false);
    static void setDrawLine();
    static void enableDepthTest();
    static void changeViewport(int width, int height);
    static void* getUserPointer(GLFWwindow* window);
    static void setUserPointer(GLFWwindow* window, void* pointer);


    void setFrameBufferSizeCallback(
        std::function<void(GLFWwindow* window, int width, int height)> frameBufferSizeCallback)
    {
        _frameBufferSizeCallback = std::move(frameBufferSizeCallback);
    }

    void setMouseCallback(std::function<void(GLFWwindow* window, double xPosIn, double yPosIn)> mouseCallback)
    {
        _mouseCallback = std::move(mouseCallback);
    }

    void setScrollCallback(std::function<void(GLFWwindow* window, float xOffset, float yOffset)> scrollCallback)
    {
        _scrollCallback = std::move(scrollCallback);
    }

    void setInputCallback(std::function<void(GLFWwindow* window, float deltaTime)> inputCallback)
    {
        _inputCallback = std::move(inputCallback);
    }

    void setLoopCallback(std::function<void(GLFWwindow* window, float delta)> loopCallback)
    {
        _loopCallback = std::move(loopCallback);
    }

private:
    GLFWwindow* _window;

    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    std::function<void(GLFWwindow* window, int width, int height)> _frameBufferSizeCallback;
    std::function<void(GLFWwindow* window, double xPosIn, double yPosIn)> _mouseCallback;
    std::function<void(GLFWwindow* window, float xOffset, float yOffset)> _scrollCallback;
    std::function<void(GLFWwindow* window, float deltaTime)> _inputCallback;
    std::function<void(GLFWwindow* window, float delta)> _loopCallback;

    float _deltaTime = 0.0f;
    float _lastTime = 0.0f;
};

#endif
