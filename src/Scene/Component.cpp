#include "Scene/Component.hpp"
using namespace Scramble::Scene;

Component::Component(Entity* entity)
    :owner(entity) {}
    
Component::~Component() {}
