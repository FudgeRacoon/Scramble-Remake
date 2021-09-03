#include "Scene/Camera.hpp"
using namespace Scramble::Scene;

Camera::Camera()
{
    this->direction = Vector3::Forward;

    this->viewportSize = 1.0;
    this->position = Vector3(0.0, 0.0, 0.0);
    this->rotation = Vector3(0.0, 0.0, 0.0);

    I32 width = RenderCommand::GetViewport().GetWidth();
    I32 height = RenderCommand::GetViewport().GetHeight();

    this->near = 100.0f; this->far = -100.0f;
    this->left = -width; this->right = width;
    this->top = height; this->bottom = -height;
}
Camera::Camera(Vector3 position)
{
    this->direction = Vector3::Forward;

    this->viewportSize = 1.0;
    this->position = position;
    this->rotation = Vector3(0.0, 0.0, 0.0);

    I32 width = RenderCommand::GetViewport().GetWidth();
    I32 height = RenderCommand::GetViewport().GetHeight();

    this->near = 100.0f; this->far = -100.0f;
    this->left = -width; this->right = width;
    this->top = height; this->bottom = -height;
}

Vector3 Camera::GetDirection()
{
    return this->direction;
}

Matrix4 Camera::GetViewMatrix()
{
    Matrix4 yaw = Matrix4::Rotate(this->rotation.x, Vector3::Right);
    Matrix4 pitch = Matrix4::Rotate(this->rotation.y, Vector3::Up);
    Matrix4 rotation = yaw * pitch;

    this->direction = (Vector3)(rotation * Vector4(0.0, 0.0, 1.0, 1.0));

    return Matrix4::LookAt(this->position, this->position + this->direction, Vector3::Up);
}
Matrix4 Camera::GetProjectionMatrix()
{
    return Matrix4::Orthographic
    (
        this->left   * this->viewportSize, 
        this->right  * this->viewportSize, 
        this->bottom * this->viewportSize, 
        this->top    * this->viewportSize, 
        this->near, 
        this->far
    );
}