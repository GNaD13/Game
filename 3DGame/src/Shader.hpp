#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <GL/glew.h>
#include "Math.h"

class Shader
{
public:
    Shader();
    ~Shader();

    bool Load(const std::string& vertShader, const std::string& fragShader);
    void Unload();

    void SetActive();

    void SetMatrixUniform(const std::string& name, const Matrix4& matrix);
private:
    bool CompileShader(const std::string& fileName, GLenum shaderType);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();
private:
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProg;
};

#endif