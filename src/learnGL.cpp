#include "Render.h"
#include "InputModule.h"

int main()
{
    Render* render = new Render();
    InputModule* input = new InputModule();

    render->Start();
    input->Start(render->GetWindow());

    while (!input->returnSignal)
    {
        input->Update();
        render->Update();
    }
    
    delete render;
    delete input;
    return 0;
}

