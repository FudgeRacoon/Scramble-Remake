#include "Input/MouseListener.hpp"
using namespace Scramble::Input;

I32* MouseListener::x = nullptr; 
I32* MouseListener::y = nullptr;
I32* MouseListener::xOffset = nullptr; 
I32* MouseListener::yOffset = nullptr;
byte* MouseListener::mouseState = nullptr;

MouseListener::MouseListener()
{
    x = new I32(0); 
    y = new I32(0);
    xOffset = new I32(0); 
    yOffset = new I32(0);
    mouseState = new byte[8];
    memset(MouseListener::mouseState, 0, 8);

    SetOnMouseButtonPress([] (MouseButtonPressedEvent* e) {mouseState[e->GetButton()] = 1;});
    SetOnMouseButtonRelease([] (MouseButtonReleasedEvent* e) {mouseState[e->GetButton()] = 0;});
    SetOnMouseMove([] (MouseMovedEvent* e) {*x = e->GetX(); *y = e->GetY();});
    SetOnMouseScroll([] (MouseScrolledEvent* e) {*xOffset = e->GetXOffset(); *yOffset = e->GetYOffset();});
}

MouseListener::~MouseListener()
{
    delete x; 
    delete y;
    delete xOffset; 
    delete yOffset;
    delete[] mouseState;
}

MouseListener* MouseListener::GetInstance()
{
    static MouseListener* instance = new MouseListener();
    return instance;
}

const byte* MouseListener::GetMouseState(I32*& x, I32*& y, I32*& xOffset, I32*& yOffset)
{
    x = MouseListener::x; 
    y = MouseListener::y;
    xOffset = MouseListener::xOffset; 
    yOffset = MouseListener::yOffset;

    return mouseState;
}