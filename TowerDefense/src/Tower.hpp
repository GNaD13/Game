#ifndef Tower_hpp
#define Tower_hpp

#include "Actor.hpp"

class SpriteComponent;
class Tower : public Actor
{
public:
    Tower(Game* game);
    ~Tower();

    virtual void UpdateActor(float deltaTime) override;

private:
    SpriteComponent* mSprite;
    float mCoolDown;
    const float mDelayTime;
};

#endif