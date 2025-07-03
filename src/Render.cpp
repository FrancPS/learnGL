#include "Render.h"

#include "InputModule.h"
#include "Shader.h"
#include "ImgLoader.h"
#include "Camera.h"

#include <stdlib.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// -- RENDER --
Render::Render()
{
    window = InitGL();
    if (!window)
    {
        std::cerr << "Failed to initialize GL" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    InputModule::GetInstance()->OnKeyPress.Register([&](int keyCode) { if (keyCode == GLFW_KEY_X) ToggleWireframeMode(); });

    camera = new Camera(SCR_WIDTH, SCR_HEIGHT);
    camera->Start(window);
}

Render::~Render()
{
    delete shaders[0];
    delete shaders[1];

    glDeleteTextures(1, &texture1);
    glDeleteTextures(1, &texture2);

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(2, VBOs);

    glfwTerminate();
}

void Render::InitTransformMatrices()
{
    modelMtx = glm::mat4(1.0f);
    modelMtx = glm::rotate(modelMtx, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Render::InitBuffers()
{
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    //unsigned int indices[] = {
    //    0, 1, 3, // first triangle
    //    1, 2, 3  // second triangle
    //};

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);

    // VERTEX ARRAY OBJECT 0
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // VERTEX ARRAY OBJECT 1
    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // ELEMENT BUFFER OBJECT
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);

    // End calls
    glBindVertexArray(0);
}

void Render::InitShaders()
{
    shaders[0] = new Shader("./src/shaders/Phong.vs", "./src/shaders/Phong.fs");
    //texture1 = LoadImg("textures/container.jpg", GL_RGB);
    //texture2 = LoadImg("textures/awesomeface.png", GL_RGBA);
    shaders[0]->Use();
    //shader1->SetInt("texture1", 0);
    //shader1->SetInt("texture2", 1);
    shaders[0]->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
    shaders[0]->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);

    shaders[1] = new Shader("./src/shaders/Phong.vs", "./src/shaders/PhongSource.fs");
    shaders[1]->Use();
    shaders[1]->SetVec3("objectColor", 1.0f, 1.0f, 1.0f);
    shaders[1]->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
}

void Render::Start()
{
    InitBuffers();
    InitTransformMatrices();
    InitShaders();
}

void Render::Update()
{
    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    camera->Update();
    // rendering commands here
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture1);
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, texture2);
    
    //Main Object
    shaders[0]->Use();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    shaders[0]->SetMat4("model", model);
    shaders[0]->SetMat4("view", camera->GetViewMatrix());
    shaders[0]->SetMat4("proj", camera->GetProjMatrix());
    shaders[0]->SetVec3("viewPos", camera->GetPosition());

    shaders[0]->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    shaders[0]->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    shaders[0]->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
    shaders[0]->SetFloat("material.shininess", 32.0f);

    glm::vec3 lightColor {sin(glfwGetTime() * 2.0f), sin(glfwGetTime() * 0.7f), sin(glfwGetTime() * 1.3f)};
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
    shaders[0]->SetVec3("light.position", lightPos);
    shaders[0]->SetVec3("light.ambient", ambientColor);
    shaders[0]->SetVec3("light.diffuse", diffuseColor);
    shaders[0]->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
    
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Light Object
    shaders[1]->Use();
    shaders[1]->SetMat4("view", camera->GetViewMatrix());
    shaders[1]->SetMat4("proj", camera->GetProjMatrix());
    glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lightPos);
    model2 = glm::scale(model2, glm::vec3(0.2f));
    shaders[1]->SetMat4("model", model2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
}

GLFWwindow* Render::InitGL()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    return window;
}

void Render::ToggleWireframeMode()
{
    static bool enabled = false;
    enabled = !enabled;

    if (enabled)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

