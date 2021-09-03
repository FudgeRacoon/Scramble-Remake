#include "Core/Application.hpp"
#include "Runtime/ScrambleGame.hpp"

int main()
{
    Scramble::Application::Start(new Scramble::ScrambleGame());
    Scramble::Application::Run();
    Scramble::Application::ShutDown();

    return EXIT_SUCCESS;
}