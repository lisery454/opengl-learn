#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include <memory>
#include <string>
#include <vector>


struct Texture2DInitInfo
{
    int wrapS;
    int wrapT;
    int minFilter;
    int magFilter;
    std::string path;
};

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    unsigned buildTexture2D(const Texture2DInitInfo& texture2DInitInfo) const;

    static void useTexture2D(int textureSlot, unsigned textureId);

private:
    std::shared_ptr<std::vector<unsigned>> _createdTextureIds;
};


#endif //TEXTURE_MANAGER_H
