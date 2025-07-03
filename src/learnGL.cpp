#include "InputModule.h"
#include "Render.h"
#include "Time/Time.h"

#include <GLFW/glfw3.h>

int main()
 {
    Render* render = new Render();
    InputModule* input = InputModule::GetInstance();

    render->Start();
    input->Start(render->GetWindow());

    while (!glfwWindowShouldClose(render->GetWindow()))
    {
        Time::Update();

        input->Update();
        render->Update();
    }
    
    delete render;
    delete input;
    return 0;
}