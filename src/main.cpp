#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader_manager.h"
#include "texture_manager.h"
#include "vao_manager.h"
#include "window_manager.h"

// float vertices[] = {
//     // positions        // colors
//     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
//     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
//     0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
// };

float vertices[] = {
    // positions      // colors        // texture coords
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // tr
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // br
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bl
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // tl
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3 // second triangle
};

int main()
{
    const auto windowManager = new WindowManager(600, 600, "GLFW window");
    const auto vaoManager = new VAOManager();
    const auto shaderManager = new ShaderManager();
    const auto textureManager = new TextureManager();

    const auto VBOId = vaoManager->buildVBO(VBOInitInfo{vertices, sizeof(vertices), GL_STATIC_DRAW});

    const auto VAOId = vaoManager->buildVAOWithEBO(VBOId,
                                                   {
                                                       {
                                                           0, 3, GL_FLOAT, GL_FALSE,
                                                           8, 0, sizeof(float)
                                                       },
                                                       {
                                                           1, 3, GL_FLOAT, GL_FALSE,
                                                           8, 3, sizeof(float)
                                                       },
                                                       {
                                                           2, 2, GL_FLOAT, GL_FALSE,
                                                           8, 6, sizeof(float)
                                                       },
                                                   }, {
                                                       indices, sizeof(indices), GL_STATIC_DRAW,
                                                   });

    const auto texture0Id = textureManager->buildTexture2D({
        GL_REPEAT,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
        "./resources/textures/tex0.jpg"
    });

    const auto texture1Id = textureManager->buildTexture2D({
        GL_REPEAT,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR,
        "./resources/textures/tex1.jpg"
    });

    TextureManager::useTexture2D(GL_TEXTURE0, texture0Id);
    TextureManager::useTexture2D(GL_TEXTURE1, texture1Id);

    const auto shaderProgramId = shaderManager->buildShader("./resources/shaders/vs_2.vert",
                                                            "./resources/shaders/fs_2.frag");

    ShaderManager::useShader(shaderProgramId);
    ShaderManager::setShaderUniform(shaderProgramId, "texture0", 0);
    ShaderManager::setShaderUniform(shaderProgramId, "texture1", 1);

    // WindowManager::setDrawLine();
    WindowManager::enableDepthTest();

    windowManager->setLoopCallback([&](GLFWwindow* window)
    {
        WindowManager::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        WindowManager::clearBuffer(true, true);

        VAOManager::drawElements(VAOId, 0, 6);
    });
    windowManager->render();

    return 0;
}
