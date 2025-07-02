#pragma once
#include <glm/gtc/matrix_transform.hpp>

struct GLFWwindow;
class Shader;
class Camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Render
{
public:
    Render();
    ~Render();
    
    void Start();
    void Update();

    GLFWwindow* GetWindow() { return window; }

private:
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

    Camera* camera {nullptr};

    glm::mat4 modelMtx;

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

