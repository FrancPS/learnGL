#include "Time.h"

#include <GLFW/glfw3.h>

void Time::Update()
{
    double currentFrame = glfwGetTime();
    DeltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
