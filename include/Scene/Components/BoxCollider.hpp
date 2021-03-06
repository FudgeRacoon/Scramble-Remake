#ifndef BOX_COLLIDER_HPP
#define BOX_COLLIDER_HPP

#include "Core/Common/Types.hpp"
#include "Core/Debug/Assert.hpp"
#include "Core/Math/Vector3.hpp"

#include "Physics/Body.hpp"
#include "Physics/Bounds.hpp"

#include "../Entity.hpp"
#include "../Component.hpp"
#include "Transform.hpp"

using namespace Scramble;
using namespace Scramble::Physics;

namespace Scramble::Scene
{
    struct ColliderProps
    {
        Bounds bounds;
        Vector3 offset;

        F32 mass;
        F32 friction;
        F32 resistution;

        F32 restitutionThreshold;

        bool isTrigger;
    };  

    class BoxCollider : public Component
    {
    private:
        Body* body;   
        Transform* transform;
    
    private:
        ColliderProps props;

    public:
        BoxCollider(Entity* owner);
        BoxCollider(Entity* owner, Vector3 size);
    
    public:
        Vector3 GetSize();
        Vector3 GetCenter();
        Vector3 GetExtents();

    public:
        F32 GetMass();
        F32 GetFriction();
        F32 GetResistution();

    public:
        bool IsTrigger();

    public:
        void SetSize(Vector3 value);
        void SetCenter(Vector3 value);
        void SetExtents(Vector3 value);

    public:
        void SetMass(F32 value);
        void SetFriction(F32 value);
        void SetResistution(F32 value);

    public:
        void SetTrigger(bool value);

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif