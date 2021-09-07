#include "Scene/Components/Tag.hpp"
using namespace Scramble::Scene;

Tag::Tag(Entity* owner, std::string tag, bool enabled) : Component(owner)
{
    this->tag = tag;
    this->enabled = enabled;
}

void Tag::Setup() {}
void Tag::Update() {}