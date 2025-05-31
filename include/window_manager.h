#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <functional>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

struct WindowCallbackInfo
{
    void (*frameBufferSizeCallback)(GLFWwindow* window, int width, int height) = nullptr;
    void (*mouseCallback)(GLFWwindow* window, double xPosIn, double yPosIn) = nullptr;
    void (*scrollCallback)(GLFWwindow* window, double xOffset, double yOffset) = nullptr;
    void (*inputCallback)(GLFWwindow* window, float deltaTime) = nullptr;
    void (*loopCallback)(GLFWwindow* window, float delta) = nullptr;
};

class WindowManager
{
public:
    WindowManager(int width, int height, const char* title, WindowCallbackInfo info);
    ~WindowManager();

    void render();

    static void setClearColor(float r, float g, float b, float a);
    static void clearBuffer(bool color = false, bool depth = false, bool stencil = false);
    static void setDrawLine();
    static void enableDepthTest();
    static void changeViewport(int width, int height);

private:
    GLFWwindow* _window;
    std::function<void(GLFWwindow* window, float)> _loopCallBack;
    std::function<void(GLFWwindow* window, float)> _inputCallBack;

    float _deltaTime = 0.0f;
    float _lastTime = 0.0f;
};

#endif
