#pragma once

struct GLFWwindow;

class Render
{

public:
    Render();
    ~Render();
    
    void processInput();
    GLFWwindow* initGL();
    void initBuffers();
    void initShaders();

    void Update();
    

private:
    GLFWwindow* window {nullptr};

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    // data
    unsigned int VAO;
    unsigned int EBO;
    unsigned int VBO;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
};

