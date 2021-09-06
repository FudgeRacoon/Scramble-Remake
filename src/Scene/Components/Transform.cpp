#include "Scene/Components/Transform.hpp"
using namespace Scramble::Scene;

Transform::Transform(Vector3 positon, Vector3 rotation, Vector3 scale)
    :positon(positon), rotation(rotation), scale(scale) {}

void Transform::Setup() {}
void Transform::Update() {}