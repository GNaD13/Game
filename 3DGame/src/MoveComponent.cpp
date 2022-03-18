#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    :   Component(owner, updateOrder),
        mForwardSpeed(100.0f),
        mAngularSpeed(30.0f)
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
        Vector3 position = mOwner->GetPosition();
        position += mOwner->GetForward() * mForwardSpeed * deltaTime;
        mOwner->SetPosition(position);
    }

    // TODO: update rotation
    if(!Math::NearZero(mAngularSpeed))
    {
        Quaternion rot = mOwner->GetRotation();
        float angle = mAngularSpeed * deltaTime;

        Quaternion inc(Vector3::UnitZ, angle);

        rot = Quaternion::Concatenate(rot, inc);
        mOwner->SetRotation(rot);
    }
}