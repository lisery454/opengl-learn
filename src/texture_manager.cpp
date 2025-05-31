#include "texture_manager.h"

#include <stdexcept>

#include "stb_image.h"
#include "glad/glad.h"

TextureManager::TextureManager()
{
    _createdTextureIds = std::make_shared<std::vector<unsigned>>(
        std::vector<unsigned>{}
    );
}

TextureManager::~TextureManager()
{
    for (auto textureId : *_createdTextureIds)
    {
        glDeleteTextures(1, &textureId);
    }
}

unsigned TextureManager::buildTexture2D(const Texture2DInitInfo& texture2DInitInfo) const
{
    unsigned textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture2DInitInfo.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture2DInitInfo.wrapT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture2DInitInfo.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture2DInitInfo.magFilter);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load(texture2DInitInfo.path.c_str(), &width, &height,
                                    &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Failed to load texture!");
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    _createdTextureIds->push_back(textureId);
    return textureId;
}

void TextureManager::useTexture2D(const int textureSlotId, const unsigned textureId)
{
    glActiveTexture(GL_TEXTURE0 + textureSlotId);
    glBindTexture(GL_TEXTURE_2D, textureId);
}
