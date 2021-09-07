#ifndef BOX_COLLIDER_HPP
#define BOX_COLLIDER_HPP

#include "Core/Common/Types.hpp"
#include "Core/Math/Vector3.hpp"

#include "Physics/Bounds.hpp"
#include "Physics/PhysicsSystem.hpp"

#include "../Entity.hpp"
#include "../Component.hpp"
#include "Transform.hpp"
#include "SpriteRenderer.hpp"

using namespace Scramble;
using namespace Scramble::Physics;

namespace Scramble::Scene
{
    class BoxCollider : public Component
    {   
    private:
        b2PolygonShape* nativeShape;

    private:
        Bounds bounds;
        Vector3 offset;

    private:
        Transform* ownerTransform;
        SpriteRenderer* ownerSpriteRenderer;
    
    public:
        BoxCollider();
    
    public:
        Vector3 GetSize();
        Vector3 GetCenter();
        Vector3 GetExtents();

    public:
        void SetSize(Vector3 value);
        void SetCenter(Vector3 value);
        void SetExtents(Vector3 value);

    public:
        void Setup() override;
        void Update() override;

    friend PhysicsSystem;
    };
}

#endif