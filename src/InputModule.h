#pragma once

#include "Events/Event.h"

struct GLFWwindow;

class InputModule
{
public:
private:
    inline static InputModule* Input {nullptr}; // Lazy Singleton  TODO: Make a ServiceLocator (App class) to handle this and other unique services 
    InputModule() {} // Private constructor to prevent instancing
    
public:
    static InputModule* GetInstance();

    void Start(GLFWwindow* _window);
    void Update();

    Event<int> OnKeyPress;
    Event<float, float> OnCursorMove;
    Event<float, float> OnMouseScroll;

private:
    void ProcessInput();

    GLFWwindow* window {nullptr};
};

