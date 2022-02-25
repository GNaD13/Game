#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"
#include <stdint.h>

class Ship : public Actor
{
public:
    Ship(Game* game);
    ~Ship();

    virtual void UpdateActor(float deltaTime) override;

    void ProcessInput(const uint8_t* state);

    float GetRightSpeed() const { return mRightSpeed; }
    void SetRightSpeed(const float& rightSpeed) { mRightSpeed = rightSpeed; }

    float GetDownSpeed() const { return mDownSpeed; }
    void SetDownSpeed(const float& downSpeed) { mDownSpeed = downSpeed; }
private:
    float mRightSpeed;
    float mDownSpeed;
};

#endif
