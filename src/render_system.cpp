#include "../include/render_system.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

float vertices[] =
{
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

extern int viewHeight = 600;
extern int viewWidth = 800;

RenderSystem::RenderSystem()
{
    vaoManager = new VAOManager();
    shaderManager = new ShaderManager();
    textureManager = new TextureManager();
    cameraManager = new CameraManager(glm::vec3(0.0f, 0.0f, 3.0f),
                                      glm::vec3(0.0f, 0.0f, -1.0f),
                                      glm::vec3(0.0f, 1.0f, 0.0f), 45.0f,
                                      static_cast<float>(viewWidth),
                                      static_cast<float>(viewHeight));
    windowManager = new WindowManager(viewWidth, viewHeight, "GLFW window");

    windowManager->setFrameBufferSizeCallback([](GLFWwindow* /*window*/, const int width, const int height)
    {
        WindowManager::changeViewport(width, height);
    });

    windowManager->setMouseCallback([&](GLFWwindow* /*window*/, const double xPosIn, const double yPosIn)
    {
        cameraManager->mouseMoveChangeDirection(xPosIn, yPosIn);
    });

    windowManager->setScrollCallback([&](GLFWwindow* /*window*/, double /*xOffset*/, const double yOffset)
    {
        cameraManager->scrollChangeFov(yOffset);
    });

    windowManager->setInputCallback([&](GLFWwindow* window, const float deltaTime)
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
    });
}

RenderSystem::~RenderSystem()
{
    delete vaoManager;
    delete shaderManager;
    delete textureManager;
    delete cameraManager;
    delete windowManager;
}

void RenderSystem::render() const
{
    const auto VBOId = vaoManager->buildVBO(VBOInitInfo{vertices, sizeof(vertices), GL_STATIC_DRAW});

    const auto VAOId = vaoManager->buildVAO(VBOId,
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

    const auto texture0Id = textureManager->buildTexture2D({
        GL_REPEAT,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
        "./resources/textures/tex0.jpg"
    });

    TextureManager::useTexture2D(0, texture0Id);

    const auto shaderProgramId = shaderManager->buildShader("./resources/shaders/vs_3.vert",
                                                            "./resources/shaders/fs_3.frag");

    ShaderManager::useShader(shaderProgramId);
    ShaderManager::setShaderUniform(shaderProgramId, "texture0", 0);

    // WindowManager::setDrawLine();
    WindowManager::enableDepthTest();

    windowManager->setLoopCallback([&](GLFWwindow* /*window*/, float /*deltaTime*/)
    {
        WindowManager::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        WindowManager::clearBuffer(true, true);

        const auto projection = cameraManager->getProjectionMatrix(viewWidth, viewHeight);
        const auto view = cameraManager->getViewMatrix();
        ShaderManager::setShaderUniform(shaderProgramId, "projection", projection);
        ShaderManager::setShaderUniform(shaderProgramId, "view", view);

        glBindVertexArray(VAOId);
        for (unsigned int i = 0; i < 10; i++)
        {
            // get model matrix
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            const float angle = static_cast<float>(i) * 20.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ShaderManager::setShaderUniform(shaderProgramId, "model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
    });

    windowManager->update();
}
