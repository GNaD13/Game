#ifndef InputComponent_hpp
#define InputComponent_hpp

#include "MoveComponent.hpp"

class InputComponent : public MoveComponent
{
public:
    InputComponent(Actor* mOwner);
    ~InputComponent();

    virtual void ProcessInput(const uint8_t* keyState) override;

    void SetMaxForwardSpeed(const float speed) { mMaxForwardSpeed = speed; }
    float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }

    void SetMaxAngularSpeed(const float speed) { mMaxAngularSpeed = speed; }
    float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }

    void SetForwardKey(const int key) { mForwardKey = key; }
    int GetForwardKey() const { return mForwardKey; }

    void SetBackKey(const int key) { mBackKey = key; }
    int GetBackKey() const { return mBackKey; }

    void SetClockWiseKey(const int key) { mClockWiseKey = key; }
    int GetClockWiseKey() const { return mClockWiseKey; }

    void SetCounterClockWiseKey(const int key) { mCounterClockWiseKey = key; }
    int GetCounterClockWiseKey() const { return mCounterClockWiseKey; }

private:
    float mMaxForwardSpeed;
    float mMaxAngularSpeed;

    int mForwardKey;
    int mBackKey;

    int mClockWiseKey;
    int mCounterClockWiseKey;
};

#endif