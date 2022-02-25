#ifndef Character_hpp
#define Character_hpp

#include "Actor.hpp"
#include <stdint.h>

class AnimSpriteComponent;

class Character : public Actor
{
public:
    Character(Game* game);
    ~Character();

    virtual void UpdateActor(float deltaTime) override;

    void ProcessInput(const uint8_t* state);

    float GetRightSpeed() const { return mRightSpeed; }
    void SetRightSpeed(const float& rightSpeed) { mRightSpeed = rightSpeed; }

    float GetDownSpeed() const { return mDownSpeed; }
    void SetDownSpeed(const float& downSpeed) { mDownSpeed = downSpeed; }
private:
    void SetAnimWalk();
    void SetAnimJump();
    void SetAnimPunch();
    float mRightSpeed;
    float mDownSpeed;
    AnimSpriteComponent* mAnim;
};

#endif