#ifndef CameraActor_hpp
#define CameraActor_hpp

#include "Actor.hpp"

class Game;
class MoveComponent;

class CameraActor : public Actor
{
public:
    CameraActor(Game* game);
    ~CameraActor();

    virtual void UpdateActor(float deltaTime) override;
    virtual void ActorInput(const uint8_t* keyState) override;
private:
    MoveComponent* mMoveComp;
};

#endif