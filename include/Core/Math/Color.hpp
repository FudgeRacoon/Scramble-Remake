#ifndef COLOR_HPP
#define COLOR_HPP

#include "../Common/Types.hpp"
#include "Math.hpp"
#include "Vector4.hpp"

namespace Scramble
{
    class Color
    {
    public:
        I32 r, g, b, a;

    public:
        Color();
        Color(I32 r, I32 g, I32 b);
        Color(I32 r, I32 g, I32 b, I32 a);

    public:
        static const Color black;
        static const Color blue;
        static const Color clear;
        static const Color cyan;
        static const Color gray;
        static const Color green;
        static const Color magenta;
        static const Color red;	   
        static const Color white;
        static const Color yellow;

    public:
        Color operator +(Color c);
        Color operator -(Color c);
        Color operator *(Color c);

    public:
        bool operator ==(Color c);
        bool operator !=(Color c);

    public:
        operator Vector4();

    public:
        static Color Lerp(Color c1, Color c2, F32 t);

    public:
        static U32 RGBToHex(Color c);
        static Color HexToRGB(U32 value);
    };
}

#endif