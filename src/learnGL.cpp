#include "Render.h"

int main()
{
    Render* render = new Render();

    render->InitBuffers();
    render->InitShaders();
    
    //LoadImg();

    render->Update();
    
    delete render;
    return 0;
}

