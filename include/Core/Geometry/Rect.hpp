#ifndef RECT_HPP
#define RECT_HPP

#include "../Math/Vector3.hpp"

namespace Scramble
{
    class Rect
    {
    private:
        float x, y;
        float width, height;
        float xMax, yMax;

    public:
        Rect() = default;
        Rect(float x, float y, float width, float height);

    public:
        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
        Vector2 GetCenter();
    
    public:
        void SetX(float x);
        void SetY(float y);
        void SetWidth(float width);
        void SetHeight(float height);
    
    public:
        bool OverLaps(Rect rect);
        bool Contains(Vector2 point);
    };
}

#endif