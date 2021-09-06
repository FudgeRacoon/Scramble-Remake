#include "Scene/Components/Transform.hpp"
using namespace Scramble::Scene;

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale)
    : position(position), rotation(rotation), scale(scale) {}

void Transform::Setup() {}
void Transform::Update() {}