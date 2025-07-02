#include "Camera.h"

#include "InputModule.h"
#include "Time/Time.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Camera::Camera(int _screenW, int _screenH) : screenW(_screenW), screenH(_screenH) {};

//TODO: Start without _window parameter
void Camera::Start(GLFWwindow* _window)
{
    window = _window;

    InputModule::GetInstance()->OnKeyPress.Register([&](int keyCode) { HandleKeyboard(keyCode); });
    InputModule::GetInstance()->OnCursorMove.Register([&](float xpos, float ypos) { HandleMouse(xpos, ypos); });
    InputModule::GetInstance()->OnMouseScroll.Register([&](float xoffset, float yoffset) { HandleScroll(xoffset, yoffset); });

    lastX = 400;
    lastY = 300; //TODO: get dinamically from window.size()
}

void Camera::Update()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

// TODO: avoid copy? Store current viewMtx and return reference?
glm::mat4x4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4x4 Camera::GetProjMatrix()
{
    return glm::perspective(glm::radians(fov), (float)screenW / (float)screenH, 0.1f, 100.0f);
}

void Camera::HandleKeyboard(int keyCode)
{
    const float cameraSpeed = 2.5f * (float)Time::DeltaTime;

    switch (keyCode)
    {
        case GLFW_KEY_A:
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        case GLFW_KEY_S:
            cameraPos -= cameraSpeed * cameraFront;
            break;
        case GLFW_KEY_D:
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        case GLFW_KEY_W:
            cameraPos += cameraSpeed * cameraFront;
            break;
        default:
            break;
    }
}

void Camera::HandleMouse(float xpos, float ypos)
{
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top.
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::HandleScroll(double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
