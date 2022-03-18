#include "Shader.hpp"
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>

Shader::Shader()
    : mFragShader(0)
    , mVertexShader(0)
    , mShaderProg(0)
{

}

Shader::~Shader()
{

}

bool Shader::Load(const std::string& vertShader, const std::string& fragShader)
{
    if(!CompileShader(vertShader, GL_VERTEX_SHADER) || !CompileShader(fragShader, GL_FRAGMENT_SHADER))
    {
        return false;
    }

    mShaderProg = glCreateProgram();
    glAttachShader(mShaderProg, mVertexShader);
    glAttachShader(mShaderProg, mFragShader);
    glLinkProgram(mShaderProg);

    if(!IsValidProgram())
    {
        return false;
    }

    return true;
}

void Shader::Unload()
{
    glDeleteProgram(mShaderProg);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
    glUseProgram(mShaderProg);
}

void Shader::SetMatrixUniform(const std::string& name, const Matrix4& matrix)
{
    GLuint location = glGetUniformLocation(mShaderProg, name.c_str());
    glUniformMatrix4fv(location, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType)
{
    std::stringstream sstream;
    std::string line;
    std::ifstream shader(fileName);
    if(shader.is_open())
    {
		while(getline(shader, line))
        {
            sstream << line << "\n";
        }
        std::string striShader = sstream.str();
		const char* src = striShader.c_str();
		
        GLuint* outShader = shaderType == GL_VERTEX_SHADER ? &mVertexShader : &mFragShader;

		*outShader = glCreateShader(shaderType);
		glShaderSource(*outShader, 1, &src, nullptr);
		glCompileShader(*outShader);

        if(!IsCompiled(*outShader))
        {
            SDL_Log("Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    else
    {
        SDL_Log("Shader file not found %s", fileName.c_str());
        return false;
    }
    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL compile failed: %s", buffer);
        return false;
    }
    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    glGetProgramiv(mShaderProg, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProg, 511, nullptr, buffer);
        SDL_Log("GLSL Link Status: %s", buffer);
        return false;
    }
    return true;
}


