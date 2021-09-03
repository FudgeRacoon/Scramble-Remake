#include "Core/WindowProps.hpp"
using namespace Scramble;

WindowProps::WindowProps(const char* title, U32 width, U32 height, 
                         U32 apiMajorVersion, U32 apiMinorVersion, 
                         bool fullscreen, bool vSync)
    : title(title), width(width), height(height), 
      apiMajorVersion(apiMajorVersion), apiMinorVersion(apiMinorVersion), 
      fullscreen(fullscreen), vSync(vSync) {}