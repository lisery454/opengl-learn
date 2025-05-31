#include "../include/shader_manager.h"

#include <sstream>

#include "glad/glad.h"

ShaderManager::ShaderManager()
{
    _createdShaderProgramIds = std::make_shared<std::vector<unsigned>>(
        std::vector<unsigned>{}
    );
}

ShaderManager::~ShaderManager()
{
    for (const auto shaderProgramId : *_createdShaderProgramIds)
    {
        glDeleteProgram(shaderProgramId);
    }
}

unsigned ShaderManager::buildShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) const
{
    // 1. read file to string
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFileStream;
    std::ifstream fShaderFileStream;
    // ensure ifstream objects can throw exceptions:
    vShaderFileStream.exceptions
        (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFileStream.exceptions
        (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFileStream.open(vertexShaderPath);
        fShaderFileStream.open(fragmentShaderPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file’s buffer contents into streams
        vShaderStream << vShaderFileStream.rdbuf();
        fShaderStream << fShaderFileStream.rdbuf();
        // close file handlers
        vShaderFileStream.close();
        fShaderFileStream.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(std::string("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ \n") + e.what());
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned vertexShaderId, fragmentShaderId;
    int success;
    char infoLog[512];

    // vertex Shader
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShaderId);
    // print compile errors if any
    glGetShaderiv
        (vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n") + infoLog);
    }

    // fragment shader
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShaderId);
    // print compile errors if any
    glGetShaderiv
        (fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog
            (fragmentShaderId, 512, nullptr, infoLog);

        throw std::runtime_error(std::string("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n") + infoLog);
    }


    // shader Program
    auto shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);
    // print linking errors if any
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("ERROR::SHADER::PROGRAM::LINKING_FAILED\n") + infoLog);
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    _createdShaderProgramIds->push_back(shaderProgramId);
    return shaderProgramId;
}

void ShaderManager::setShaderUniform(const unsigned shaderProgramId, const std::string& name, const int value)
{
    const auto loc = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1i(loc, value);
}

void ShaderManager::setShaderUniform(const unsigned shaderProgramId, const std::string& name, const bool value)
{
    const auto loc = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1i(loc, static_cast<int>(value));
}

void ShaderManager::setShaderUniform(const unsigned shaderProgramId, const std::string& name, const float value)
{
    const auto loc = glGetUniformLocation(shaderProgramId, name.c_str());
    glUniform1f(loc, value);
}

void ShaderManager::useShader(const unsigned shaderId)
{
    glUseProgram(shaderId);
}
