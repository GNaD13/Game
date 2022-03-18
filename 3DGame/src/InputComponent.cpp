#include "InputComponent.hpp"

InputComponent::InputComponent(Actor* owner)
    :   MoveComponent(owner)
{

}

InputComponent::~InputComponent()
{

}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
    float forwardSpeed = 0.0f;
    if(keyState[mForwardKey])
    {
        forwardSpeed += mMaxForwardSpeed;
    }

    if(keyState[mBackKey])
    {
        forwardSpeed -= mMaxForwardSpeed;
    }
    SetForwardSpeed(forwardSpeed);

    float angularSpeed = 0.0f;
    if(keyState[mClockWiseKey])
    {
        angularSpeed += mMaxAngularSpeed;
    }

    if(keyState[mCounterClockWiseKey])
    {
        angularSpeed -= mMaxAngularSpeed;
    }
    SetAngularSpeed(angularSpeed);
}