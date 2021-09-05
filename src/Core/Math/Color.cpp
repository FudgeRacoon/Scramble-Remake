#include "Core/Math/Color.hpp"
using namespace Scramble;

const Color Color::white   = Color(255, 255, 255, 255);
const Color Color::black   = Color(0, 0, 0, 255);
const Color Color::red     = Color(255, 0, 0, 255);	  
const Color Color::green   = Color(0, 255, 0, 255);
const Color Color::blue    = Color(0, 0, 255, 255);
const Color Color::clear   = Color(0, 0, 0, 0);
const Color Color::cyan    = Color(0, 255, 255, 255);
const Color Color::gray    = Color(128, 128, 128, 255);
const Color Color::magenta = Color(255, 0, 255, 255);
const Color Color::yellow  = Color(255, 235, 4, 255);

Color::Color()
    :r(0), g(0), b(0), a(255) {}
Color::Color(I32 r, I32 g, I32 b)
    :r(r), g(g), b(b), a(255) {}
Color::Color(I32 r, I32 g, I32 b, I32 a)
    :r(r), g(g), b(b), a(a) {}

Color Color::operator +(Color c)
{
    Color result;

    result.r = Math::Clamp(this->r + c.r, 0, 255);
    result.g = Math::Clamp(this->g + c.g, 0, 255);
    result.b = Math::Clamp(this->b + c.b, 0, 255);

    return result;
}
Color Color::operator -(Color c)
{
    Color result;

    result.r = Math::Clamp(this->r - c.r, 0, 255);
    result.g = Math::Clamp(this->g - c.g, 0, 255);
    result.b = Math::Clamp(this->b - c.b, 0, 255);

    return result;
}
Color Color::operator *(Color c)
{
    Color result;

    result.r = Math::Clamp(this->r * c.r, 0, 255);
    result.g = Math::Clamp(this->g * c.g, 0, 255);
    result.b = Math::Clamp(this->b * c.b, 0, 255);

    return result;
}
bool Color::operator ==(Color c)
{
    return this->r == c.r &&
            this->g == c.g &&
            this->b == c.b &&
            this->a == c.a;
}
bool Color::operator !=(Color c)
{
    return this->r != c.r &&
            this->g != c.g &&
            this->b != c.b &&
            this->a != c.a;
}
Color::operator Vector4()
{
    return Vector4((float)this->r, (float)this->g, (float)this->b, (float)this->a);
}

Color Color::Lerp(Color c1, Color c2, F32 t)
{
    t = Math::Clamp(t, 0, 1);

    return Color
    (
        c1.r +(c2.r - c1.r) * t,
        c1.g +(c2.g - c1.g) * t,
        c1.b +(c2.b - c1.b) * t,
        c1.a +(c2.a - c1.a) * t
    );
}

U32 Color::RGBToHex(Color c)
{
    return c.r << 24 | c.g << 16 | c.b << 8 | c.a;
}
Color Color::HexToRGB(U32 value)
{
    Color color;

    color.r = value >> 24;
    color.g = value >> 16;
    color.b = value >> 8;
    color.a = value & 0xFF; 

    return color;
}