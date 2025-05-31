#ifndef VAO_MANAGER_H
#define VAO_MANAGER_H
#include <memory>
#include <vector>


struct VAOInitInfo
{
    unsigned id;
    int dimensions;
    unsigned type;
    bool isNormalize;
    int stride;
    int offset;
    int sizeOfElement;
};

struct VBOInitInfo
{
    float* vertices;
    unsigned totalSize;
    unsigned mode;
};

struct EBOInitInfo
{
    unsigned* indices;
    unsigned totalSize;
    unsigned mode;
};

class VAOManager
{
public:
    VAOManager();
    ~VAOManager();

    unsigned buildVBO(const VBOInitInfo& info) const;
    unsigned buildVAO(unsigned VBOId, const std::vector<VAOInitInfo>& vaoInitInfos) const;
    unsigned buildVAOWithEBO(unsigned VBOId, const std::vector<VAOInitInfo>& vaoInitInfos,
                             const EBOInitInfo& eboInitInfo) const;

    static void drawTriangles(unsigned VAOId, int index = 0, int count = 3);
    static void drawElements(unsigned VAOId, int index = 0, int count = 3);

private:
    std::shared_ptr<std::vector<unsigned>> _createdVAOIds;
    std::shared_ptr<std::vector<unsigned>> _createdVBOIds;
    std::shared_ptr<std::vector<unsigned>> _createdEBOIds;
};


#endif //VAO_MANAGER_H
