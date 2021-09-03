#ifndef WINDOWPROPS_HPP
#define WINDOWPROPS_HPP

#include "Common/Types.hpp"

namespace Scramble
{
    struct WindowProps
    {
        const char* title;
        U32 width, height;

        U32 apiMajorVersion, apiMinorVersion;
        
        bool fullscreen;
        bool vSync;

        WindowProps(const char* title = "Scramble", U32 width = 800, U32 height = 600, 
                    U32 apiMajorVersion = 4, U32 apiMinorVersion = 4, 
                    bool fullscreen = false, bool vSync = true); 
    };
}

#endif