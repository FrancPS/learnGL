#include <iostream>

#include "Render.h"



int main()
{
    Render* render = new Render();

    render->initBuffers();
    render->initShaders();

    render->Update();

    
    delete render;
    return 0;
}

