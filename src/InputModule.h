#pragma once

struct GLFWwindow;

class InputModule
{
public:
    InputModule() {};
    ~InputModule() {};

    void Start(GLFWwindow* _window);
    void Update();

    bool returnSignal {false};

private:
    void ProcessInput();
    void ToggleWireframeMode();

    GLFWwindow* window;
};

