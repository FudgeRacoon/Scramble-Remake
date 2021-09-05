#ifndef WINDOWPROPS_HPP
#define WINDOWPROPS_HPP

#include "Common/Types.hpp"

namespace Scramble
{
    struct WindowProps
    {
    public:
        const char* title;
    
    public:
        U32 width, height;
    
    public:
        bool fullscreen;
        bool vSync;

    public:
        WindowProps()
        {
            this->title = "Scramble";

            this->width = 800;
            this->height = 600;

            this->fullscreen = false;
            this->vSync = true;
        }
    };
}

#endif