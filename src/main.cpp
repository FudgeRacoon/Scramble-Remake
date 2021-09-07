#include "Core/Application.hpp"
#include "Runtime/ScrambleGame.hpp"

#include "Box2D/include/box2d/box2d.h"

int main()
{
    Scramble::Application::Start(new Scramble::ScrambleGame());
    Scramble::Application::Run();
    Scramble::Application::ShutDown();

    return EXIT_SUCCESS;
}