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

    Shader* shaders[2] {nullptr, nullptr};

    unsigned int texture1;
    unsigned int texture2;

    Camera* camera {nullptr};

    glm::mat4 modelMtx;
};

