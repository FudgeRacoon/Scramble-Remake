#include "Core/WindowProps.hpp"
using namespace Scramble;

WindowProps::WindowProps(const char* title, 
                         U32 width, U32 height, 
                         bool fullscreen, bool vSync)
    : title(title), 
      width(width), height(height),  
      fullscreen(fullscreen), vSync(vSync) {}