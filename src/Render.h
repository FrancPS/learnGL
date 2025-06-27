#pragma once
#include <glm/gtc/matrix_transform.hpp>

struct GLFWwindow;
class Shader;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Render
{
public:
    Render();
    ~Render();
    
    void Start();
    void Update();
    
    bool returnSignal {false};

private:
    void ProcessInput();
    GLFWwindow* InitGL();
    void InitBuffers();
    void InitTransform();
    void InitShaders();
    void ToggleWireframeMode();
    
    GLFWwindow* window {nullptr};

    // data
    unsigned int VAOs[2];
    unsigned int EBO;
    unsigned int VBOs[2];

    Shader* shader1 {nullptr};

    unsigned int texture1;
    unsigned int texture2;
    glm::mat4 transformMatx;
};

