#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>



class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    unsigned buildShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) const;
    static void setShaderUniform(unsigned shaderProgramId, const std::string& name, int value);
    static void setShaderUniform(unsigned shaderProgramId, const std::string& name, bool value);
    static void setShaderUniform(unsigned shaderProgramId, const std::string& name, float value);
    static void setShaderUniform(unsigned shaderProgramId, const std::string& name, const glm::mat4& value);
    static void useShader(unsigned shaderId);

private:
    std::shared_ptr<std::vector<unsigned>> _createdShaderProgramIds;
};


#endif //SHADER_MANAGER_H
