#pragma once

#include <string>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Use() const; // use/activate the shader

    // utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;

private:
    unsigned int CreateShader(int shaderType, const char* source);
    unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);
};
