#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    :   Component(owner, updateOrder),
        mForwardSpeed(0.0f),
        mAngularSpeed(0.0f)
{

}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::Update(float deltaTime)
{
    // TODO: update position
    if(!Math::NearZero(mForwardSpeed))
    {
        Vector2 position = mOwner->GetPosition();
        position += mOwner->GetForward() * mForwardSpeed * deltaTime;
        mOwner->SetPosition(position);
    }

    // TODO: update rotation
    if(!Math::NearZero(mAngularSpeed))
    {
        float rotation = mOwner->GetRotation();
        rotation += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rotation);
    }
}