#ifndef Ship_hpp
#define Ship_hpp

#include "Actor.hpp"

class CircleComponent;

class Ship : public Actor
{
public:
    Ship(Game* game);
    ~Ship();

    virtual void UpdateActor(float deltaTime) override;
    virtual void ActorInput(const uint8_t* keyState) override;

    CircleComponent* GetCircle() const { return mCircle; }
private:
    CircleComponent* mCircle;
    float mCooldown;
    float mReborn;
};

#endif