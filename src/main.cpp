#include <iostream>
#include <glad/glad.h>
#include "shader_manager.h"
#include "texture_manager.h"
#include "vao_manager.h"
#include "window_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera_manager.h"


// float vertices[] = {
//     // positions        // colors
//     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
//     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
//     0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
// };

// float vertices[] = {
//     // positions      // colors        // texture coords
//     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // tr
//     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // br
//     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bl
//     -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // tl
// };
//
// unsigned int indices[] = {
//     0, 1, 3, // first triangle
//     1, 2, 3 // second triangle
// };

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)
};

constexpr auto viewWidth = 800;
constexpr auto viewHeight = 600;

unsigned VBOId, VAOId, shaderProgramId, texture0Id;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void inputCallback(GLFWwindow* window, float deltaTime);
void loopCallback(GLFWwindow* window, float deltaTime);

const auto vaoManager = new VAOManager();
const auto shaderManager = new ShaderManager();
const auto textureManager = new TextureManager();
const auto cameraManager = new CameraManager(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                                             glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, viewWidth, viewHeight);


int main()
{
    WindowCallbackInfo windowCallbackInfo;
    windowCallbackInfo.frameBufferSizeCallback = frameBufferSizeCallback;
    windowCallbackInfo.mouseCallback = mouseCallback;
    windowCallbackInfo.scrollCallback = scrollCallback;
    windowCallbackInfo.inputCallback = inputCallback;
    windowCallbackInfo.loopCallback = loopCallback;
    const auto windowManager = new WindowManager(viewWidth, viewHeight, "GLFW window", windowCallbackInfo);

    VBOId = vaoManager->buildVBO(VBOInitInfo{vertices, sizeof(vertices), GL_STATIC_DRAW});

    VAOId = vaoManager->buildVAO(VBOId,
                                 {
                                     // position
                                     {
                                         0, 3, GL_FLOAT, GL_FALSE,
                                         5, 0, sizeof(float)
                                     },
                                     // texcoord
                                     {
                                         1, 2, GL_FLOAT, GL_FALSE,
                                         5, 3, sizeof(float)
                                     },
                                 });

    texture0Id = textureManager->buildTexture2D({
        GL_REPEAT,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
        "./resources/textures/tex0.jpg"
    });

    TextureManager::useTexture2D(0, texture0Id);

    shaderProgramId = shaderManager->buildShader("./resources/shaders/vs_3.vert",
                                                 "./resources/shaders/fs_3.frag");

    ShaderManager::useShader(shaderProgramId);
    ShaderManager::setShaderUniform(shaderProgramId, "texture0", 0);

    // WindowManager::setDrawLine();
    WindowManager::enableDepthTest();

    windowManager->render();

    return 0;
}


void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    WindowManager::changeViewport(width, height);
}

void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn)
{
    cameraManager->mouseMoveChangeDirection(xPosIn, yPosIn);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    cameraManager->scrollChangeFov(yOffset);
}

void inputCallback(GLFWwindow* window, const float deltaTime)
{
    const auto cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraManager->keyboardInputChangePosition(W, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraManager->keyboardInputChangePosition(S, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraManager->keyboardInputChangePosition(A, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraManager->keyboardInputChangePosition(D, cameraSpeed);
}

void loopCallback(GLFWwindow* window, float deltaTime)
{
    WindowManager::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    WindowManager::clearBuffer(true, true);

    auto projection = cameraManager->getProjectionMatrix(viewWidth, viewHeight);
    auto view = cameraManager->getViewMatrix();
    ShaderManager::setShaderUniform(shaderProgramId, "projection", projection);
    ShaderManager::setShaderUniform(shaderProgramId, "view", view);

    glBindVertexArray(VAOId);

    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        auto model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[i]);
        const float angle = static_cast<float>(i) * 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        ShaderManager::setShaderUniform(shaderProgramId, "model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}
