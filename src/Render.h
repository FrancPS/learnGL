#pragma once

#include <glad/glad.h>

struct GLFWwindow;

class Render
{
private:
    enum ShaderType
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

public:
    Render();
    ~Render();
    
    void initBuffers();
    void initShaders();

    void Update();
    

private:
    unsigned int CreateShader(ShaderType shaderType, const char* source);
    unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

    void processInput();
    GLFWwindow* initGL();

    GLFWwindow* window {nullptr};

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSourceOrange = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
    const char* fragmentShaderSourceYellow = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
        "}\n\0";
    const char* fragmentShaderSourceVariableGreen = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n"
        "}\n\0";

    // data
    unsigned int VAOs[2];
    unsigned int EBO;
    unsigned int VBOs[2];
    unsigned int vertexShader;
    unsigned int fragmentShaderOrange;
    unsigned int fragmentShaderYellow;
    unsigned int fragmentShaderVariableGreen;
    unsigned int shaderProgramOrange;
    unsigned int shaderProgramYellow;
    unsigned int shaderProgramVariableGreen;
};

