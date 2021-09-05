#include "Input/MouseListener.hpp"
using namespace Scramble::Input;

MouseListener* MouseListener::GetInstance()
{
    static MouseListener* instance = new MouseListener();
    return instance;
}

MouseListener::MouseListener()
{
    MouseListener::x = new I32(0); 
    MouseListener::y = new I32(0);
    MouseListener::xOffset = new I32(0); 
    MouseListener::yOffset = new I32(0);
    MouseListener::mouseState = new byte[8];
    memset(MouseListener::mouseState, 0, 8);

    SetOnMouseButtonPress([] (MouseButtonPressedEvent* e) {mouseState[e->GetButton()] = 1;});
    SetOnMouseButtonRelease([] (MouseButtonReleasedEvent* e) {mouseState[e->GetButton()] = 0;});
    SetOnMouseMove([] (MouseMovedEvent* e) {*x = e->GetX(); *y = e->GetY();});
    SetOnMouseScroll([] (MouseScrolledEvent* e) {*xOffset = e->GetXOffset(); *yOffset = e->GetYOffset();});
}

MouseListener::~MouseListener()
{
    delete MouseListener::x; 
    delete MouseListener::y;
    delete MouseListener::xOffset; 
    delete MouseListener::yOffset;
    delete[] MouseListener::mouseState;
}

const byte* MouseListener::GetMouseState(I32*& x, I32*& y, I32*& xOffset, I32*& yOffset)
{
    x = MouseListener::x; 
    y = MouseListener::y;
    xOffset = MouseListener::xOffset; 
    yOffset = MouseListener::yOffset;

    return MouseListener::mouseState;
}