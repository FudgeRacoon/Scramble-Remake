#ifndef SCRAMBLEGAME_HPP
#define SCRAMBLEGAME_HPP

#include "Core/RuntimeInstance.hpp"

namespace Scramble
{
    class ScrambleGame : public RuntimeInstance
    {
    public:
        void OnEnter() override;
        void OnUpdate() override;
        void OnExit() override;
    };
}

#endif