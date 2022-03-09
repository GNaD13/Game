#ifndef CircleComponent_hpp
#define CircleComponent_hpp

#include "Component.hpp"
#include "Math.h"

class CircleComponent : public Component
{
public:
    CircleComponent(Actor* owner);
    ~CircleComponent();

    void SetRadius(float radius) { mRadius = radius; }
    float GetRadius() const { return mRadius; }

    const Vector2& GetCenter() const;
private:
    float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);

#endif