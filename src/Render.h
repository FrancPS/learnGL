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
    void InitTransformMatrices();
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

    glm::mat4 modelMtx;
    glm::mat4 viewMtx;
    glm::mat4 projMtx;

    glm::vec3 cubePositions[10] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
};

