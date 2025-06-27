#include "Render.h"

int main()
{
    Render* render = new Render();

    render->Start();

    while (!render->returnSignal)
    {
        render->Update();
    }
    
    delete render;
    return 0;
}

