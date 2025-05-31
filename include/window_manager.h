#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <functional>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

class WindowManager
{
public:
    WindowManager(int width, int height, const char* title);
    ~WindowManager();

    void render() const;
    void setLoopCallback(const std::function<void(GLFWwindow*)>&);

    static void setClearColor(float r, float g, float b, float a);
    static void clearBuffer(bool color = false, bool depth = false, bool stencil = false);
    static void setDrawLine();
    static void enableDepthTest();

private:
    GLFWwindow* _window;
    std::function<void(GLFWwindow*)> _loopCallBack;
};

#endif
