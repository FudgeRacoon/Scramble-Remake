#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Core/Common/Types.hpp"
#include "Core/Math/Matrix4.hpp"
#include "Core/Math/Vector3.hpp"

#include "Graphics/RenderCommand.hpp"
using namespace Scramble;
using namespace Scramble::Graphics;

namespace Scramble::Scene
{
    class Camera
    {
    private:
        Vector3 direction;

    public:
        F32 viewportSize;
        Vector3 position;
        Vector3 rotation;

    public:
        F32 near, far;
        F32 left, right;
        F32 top, bottom;

    public:
        Camera();
        Camera(Vector3 position);

    public:
        Vector3 GetDirection();

    public:
        Matrix4 GetViewMatrix();
        Matrix4 GetProjectionMatrix();
    };
}

#endif