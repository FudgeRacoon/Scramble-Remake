#include "Core/Application.hpp"
#include "Runtime/ScrambleGame.hpp"

#include <stdio.h>

int main()
{
    Scramble::Application::Start(new Scramble::ScrambleGame());
    Scramble::Application::Run();
    Scramble::Application::ShutDown();
    
    return EXIT_SUCCESS;
}