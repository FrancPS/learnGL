#include "Render.h"

#include <stdlib.h>
#include <iostream>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // TODO Add this function as a class member?
    glViewport(0, 0, width, height);
}



// -- RENDER
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

Render::Render()
{
    window = initGL();
    if (!window)
    {
        std::cerr << "Failed to initialize GL" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

Render::~Render()
{
    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);
    glDeleteShader(fragmentShaderVariableGreen);
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);
    glDeleteProgram(shaderProgramVariableGreen);

    glfwTerminate();
}

void Render::initBuffers()
{
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,   // first triangle
    };

    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(1, &EBO);

    // VERTEX ARRAY OBJECT 0
    glBindVertexArray(VAOs[0]);

    // VERTEX BUFFER OBJECT 0
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

    // Vertex Attr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VERTEX ARRAY OBJECT 1
    glBindVertexArray(VAOs[1]);

    // VERTEX BUFFER OBJECT 1
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

    // Vertex Attr
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ELEMENT BUFFER OBJECT
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // End calls
    glBindVertexArray(0);
    

    // Wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Render::initShaders()
{
    // VERTEX SHADER
    vertexShader = CreateShader(ShaderType::VERTEX, vertexShaderSource);

    // FRAGMENT SHADER
    fragmentShaderOrange = CreateShader(ShaderType::FRAGMENT, fragmentShaderSourceOrange);
    fragmentShaderYellow = CreateShader(ShaderType::FRAGMENT, fragmentShaderSourceYellow);
    fragmentShaderVariableGreen = CreateShader(ShaderType::FRAGMENT, fragmentShaderSourceVariableGreen);

    // SHADER PROGRAM
    shaderProgramOrange = CreateProgram(vertexShader, fragmentShaderOrange);
    shaderProgramYellow = CreateProgram(vertexShader, fragmentShaderYellow);
    shaderProgramVariableGreen = CreateProgram(vertexShader, fragmentShaderVariableGreen);
}

void Render::Update()
{
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput();

        // rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgramVariableGreen);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgramVariableGreen, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

unsigned int Render::CreateShader(ShaderType shaderType, const char* source)
{
    unsigned int shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    return shader;
}

unsigned int Render::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int  success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    return program;
}

void Render::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* Render::initGL()
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