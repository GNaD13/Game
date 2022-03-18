#include "CircleComponent.hpp"
#include"Actor.hpp"
#include <iostream>

CircleComponent::CircleComponent(Actor* owner)
    :   Component(owner)
{

}

CircleComponent::~CircleComponent()
{

}

const Vector3& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    Vector3 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();
    
    float radiiSum = a.GetRadius() + b.GetRadius();
    float radiiSumSq;
    radiiSumSq = radiiSum * radiiSum;

    return distSq <= radiiSumSq;
}