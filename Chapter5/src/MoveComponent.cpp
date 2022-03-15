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
        Vector2 position = mOwner->GetPosition();
        position += mOwner->GetForward() * mForwardSpeed * deltaTime;

        // if (position.x < -512.0f) { position.x = 510.0f; }
		// else if (position.x > 512.0f) { position.x = -510.0f; }
		// if (position.y < -384.0f) { position.y = 382.0f; }
		// else if (position.y > 384.0f) { position.y = -382.0f; }
        
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