#include "InputModule.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//TODO: Start without a function
void InputModule::Start(GLFWwindow* _window)
{
    window = _window;
}

void InputModule::Update()
{
    ProcessInput();

    if (glfwWindowShouldClose(window))
    {
        returnSignal = true;
        return;
    }
}

void InputModule::ProcessInput()
{
    static bool wKeyWasPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (!wKeyWasPressed)
        {
            //TODO: Render->ToggleWireframeMode();
            ToggleWireframeMode();
            wKeyWasPressed = true;
        }
    }
    else
    {
        wKeyWasPressed = false;
    }
}

void InputModule::ToggleWireframeMode()
{
    static bool enabled = false;

    if (enabled)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    enabled = !enabled;
}