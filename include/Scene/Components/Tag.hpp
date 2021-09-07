#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string>

#include "../Component.hpp"

namespace Scramble::Scene
{
    class Tag : public Component
    {
    public:
        std::string tag;
        bool enabled;

    public:
        Tag(Entity* owner, std::string tag, bool enabled = true);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif