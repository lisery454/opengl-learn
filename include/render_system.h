#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "camera_manager.h"
#include "shader_manager.h"
#include "texture_manager.h"
#include "vao_manager.h"
#include "window_manager.h"

extern float vertices[];

extern glm::vec3 cubePositions[];

extern int viewHeight;
extern int viewWidth;


class RenderSystem
{
public:
    RenderSystem();
    ~RenderSystem();
    void render() const;

private:
   VAOManager* vaoManager;
   ShaderManager* shaderManager;
   TextureManager* textureManager;
   CameraManager* cameraManager;
   WindowManager* windowManager;
};

#endif //RENDER_SYSTEM_H
