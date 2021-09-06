#include "Input/KeyListener.hpp"
using namespace Scramble::Input;

byte* KeyListener::keyboardStates = nullptr;

KeyListener::KeyListener()
{
    keyboardStates = new byte[512];
    memset(keyboardStates, 0, 512);

    SetOnKeyPress([] (KeyPressedEvent* e) {keyboardStates[e->GetKey()] = 1;});
    SetOnKeyRelease([] (KeyReleasedEvent* e) {keyboardStates[e->GetKey()] = 0;});
}

KeyListener::~KeyListener()
{
    delete[] keyboardStates;
}

KeyListener* KeyListener::GetInstance()
{
    static KeyListener* instance = new KeyListener();
    return instance;
}

const byte* KeyListener::GetKeyboardState()
{
    return keyboardStates;
}

