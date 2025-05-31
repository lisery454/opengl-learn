#include "vao_manager.h"

#include <iostream>

#include "glad/glad.h"

VAOManager::VAOManager()
{
    _createdVAOIds = std::make_shared<std::vector<unsigned>>(
        std::vector<unsigned>{}
    );

    _createdVBOIds = std::make_shared<std::vector<unsigned>>(
        std::vector<unsigned>{}
    );

    _createdEBOIds = std::make_shared<std::vector<unsigned>>(
       std::vector<unsigned>{}
   );
}

VAOManager::~VAOManager()
{
    for (auto VBOId : *_createdVBOIds)
    {
        glDeleteBuffers(1, &VBOId);
    }

    for (auto VAOId : *_createdVAOIds)
    {
        glDeleteVertexArrays(1, &VAOId);
    }

    for (auto EBOId : *_createdEBOIds)
    {
        glDeleteBuffers(1, &EBOId);
    }
}

unsigned VAOManager::buildVBO(const VBOInitInfo& info) const
{
    unsigned VBOId;
    glGenBuffers(1, &VBOId);
    // input data to VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBOId); // binding
    glBufferData(GL_ARRAY_BUFFER, info.totalSize,
                 info.vertices, info.mode);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinding

    _createdVBOIds->push_back(VBOId);
    return VBOId;
}

unsigned VAOManager::buildVAO(const unsigned VBOId, const std::vector<VAOInitInfo>& vaoInitInfos) const
{
    unsigned VAOId;
    glGenVertexArrays(1, &VAOId);

    // bind
    glBindVertexArray(VAOId);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId);

    for (const auto& vaoInitInfo : vaoInitInfos)
    {
        glEnableVertexAttribArray(vaoInitInfo.id);
        glVertexAttribPointer(vaoInitInfo.id, vaoInitInfo.dimensions, vaoInitInfo.type, vaoInitInfo.isNormalize,
                              vaoInitInfo.stride * vaoInitInfo.sizeOfElement,
                              reinterpret_cast<void*>(vaoInitInfo.offset * vaoInitInfo.sizeOfElement));
    }

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _createdVAOIds->push_back(VAOId);
    return VAOId;
}

unsigned VAOManager::buildVAOWithEBO(const unsigned VBOId, const std::vector<VAOInitInfo>& vaoInitInfos,
                                     const EBOInitInfo& eboInitInfo) const
{
    unsigned VAOId;
    glGenVertexArrays(1, &VAOId);

    // bind
    glBindVertexArray(VAOId);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId);

    for (const auto& vaoInitInfo : vaoInitInfos)
    {
        glEnableVertexAttribArray(vaoInitInfo.id);
        glVertexAttribPointer(vaoInitInfo.id, vaoInitInfo.dimensions, vaoInitInfo.type, vaoInitInfo.isNormalize,
                              vaoInitInfo.stride * vaoInitInfo.sizeOfElement,
                              reinterpret_cast<void*>(vaoInitInfo.offset * vaoInitInfo.sizeOfElement));
    }


    unsigned EBOId;
    glGenBuffers(1, &EBOId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboInitInfo.totalSize,
                 eboInitInfo.indices, eboInitInfo.mode);

    _createdEBOIds->push_back(EBOId);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    _createdVAOIds->push_back(VAOId);
    return VAOId;
}

void VAOManager::drawTriangles(const unsigned VAOId, const int index, const int count)
{
    glBindVertexArray(VAOId);
    glDrawArrays(GL_TRIANGLES, index, count);
    glBindVertexArray(0);
}

void VAOManager::drawElements(const unsigned VAOId, const int index, const int count)
{
    glBindVertexArray(VAOId);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, reinterpret_cast<void*>(index));
    glBindVertexArray(0);
}
