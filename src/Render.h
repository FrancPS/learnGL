#pragma once

#include <glad/glad.h>

struct GLFWwindow;
class Shader;

class Render
{
public:
    Render();
    ~Render();
    
    void initBuffers();
    void initShaders();

    void Update();
    

private:
    void processInput();
    GLFWwindow* initGL();

    GLFWwindow* window {nullptr};

    // data
    unsigned int VAOs[2];
    unsigned int EBO;
    unsigned int VBOs[2];

    Shader* shader1 {nullptr};
};

