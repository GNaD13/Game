#ifndef LightPointActor_hpp
#define LightPointActor_hpp

#include "Actor.hpp"
#include "Math.h"

class MoveComponent;

class LightPointActor : public Actor
{
public:
    LightPointActor(Game* game);
    ~LightPointActor();

    virtual void UpdateActor(float deltaTime) override;
    virtual void ActorInput(const uint8_t* keyState) override;
private:
    MoveComponent* mMoveComp;
};

#endif