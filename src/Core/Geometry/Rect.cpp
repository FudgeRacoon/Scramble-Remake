#include "Core/Geometry/Rect.hpp"
using namespace Scramble;

Rect::Rect(Vector3 position, Vector2 size)
{
    this->x = position.x; this->y = position.y;
    this->width = size.x; this->height = size.y;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;
}
Rect::Rect(float x, float y, float width, float height)
{   
    this->x = x; this->y = y;
    this->width = width; this->height = height;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;
}

float Rect::GetX()
{
    return this->x;
}
float Rect::GetY()
{
    return this->y;
}
float Rect::GetXMax()
{
    return this->xMax;
}
float Rect::GetYMax()
{
    return this->yMax;
}   
float Rect::GetWidth()
{
    return this->width;
}
float Rect::GetHeight()
{
    return this->height;
}
Vector2 Rect::GetCenter()
{
    return Vector2(this->x + (this->width / 2), this->y - (this->height / 2));
}

void Rect::SetX(float x)
{
    this->x = x;
    this->xMax = this->x + this->width;
}
void Rect::SetY(float y)
{
    this->y = y;
    this->yMax = this->y - this->height;
}
void Rect::SetWidth(float width)
{
    this->width = width;
    this->xMax = this->x + this->width;
}
void Rect::SetHeight(float height)
{
    this->height = height;
    this->yMax = this->y - this->height;
}

bool Rect::OverLaps(Rect rect)
{
    if(rect.xMax >= this->x && rect.x <= this->xMax &&
       rect.yMax <= this->y && rect.y >= this->yMax)
        return true;
    else
        return false;
}
bool Rect::Contains(Vector2 point)
{
    if(point.x >= this->x && point.x <= this->xMax &&
       point.y <= this->y && point.y >= this->yMax)
        return true;
    else
        return false;
}