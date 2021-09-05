#ifndef WINDOWPROPS_HPP
#define WINDOWPROPS_HPP

#include "Common/Types.hpp"

namespace Scramble
{
    struct WindowProps
    {
        const char* title;
        
        U32 width, height;
        
        bool fullscreen;
        bool vSync;

        WindowProps(const char* title = "Scramble", 
                    U32 width = 800, U32 height = 600, 
                    bool fullscreen = false, bool vSync = true); 
    };
}

#endif