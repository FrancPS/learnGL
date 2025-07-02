#include "InputModule.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    InputModule::GetInstance()->OnCursorMove.Trigger((float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    InputModule::GetInstance()->OnMouseScroll.Trigger((float)xoffset, (float)yoffset);
}

InputModule* InputModule::GetInstance()
{
    if (!Input)
        Input = new InputModule();
    return Input;
}

//TODO: Start without a parameter
void InputModule::Start(GLFWwindow* _window)
{
    window = _window;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void InputModule::Update()
{
    glfwPollEvents();
    ProcessInput();
}

void InputModule::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        InputModule::GetInstance()->OnKeyPress.Trigger(GLFW_KEY_A);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        InputModule::GetInstance()->OnKeyPress.Trigger(GLFW_KEY_S);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        InputModule::GetInstance()->OnKeyPress.Trigger(GLFW_KEY_D);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        InputModule::GetInstance()->OnKeyPress.Trigger(GLFW_KEY_W);

    static bool XKeyWasPressed = false; // Hack to avoid call a Trigger on every frame
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        if (!XKeyWasPressed)
        {
            InputModule::GetInstance()->OnKeyPress.Trigger(GLFW_KEY_X);
            XKeyWasPressed = true;
        }
    }
    else
    {
        XKeyWasPressed = false;
    }
}