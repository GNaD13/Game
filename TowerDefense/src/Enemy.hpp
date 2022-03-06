#ifndef Enemy_hpp
#define Enemy_hpp

#include "Actor.hpp"

class SpriteComponent;
class MoveComponent;
class Enemy : public Actor
{
public:
    Enemy(Game* game);
    ~Enemy();

    virtual void UpdateActor(float deltaTime);
private:
    SpriteComponent* mSprite;
    MoveComponent* mMove;
};

#endif