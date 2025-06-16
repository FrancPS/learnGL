#include <iostream>

#include "Render.h"



int main()
{
    Render* render = new Render();

    if (!render)
    {
        std::cout << "Failed to initialize Render class" << std::endl;
        return -1;
    }

    render->initBuffers();
    render->initShaders();

    render->Update();

    delete render;

    return 0;
}

