#ifndef Asteroid_hpp
#define Asteroid_hpp

#include "Actor.hpp"

class CircleComponent;

class Asteroid : public Actor
{
public:
    Asteroid(Game* game);
    ~Asteroid();

    virtual void UpdateActor(float deltaTime) override;
    CircleComponent* GetCircle() const { return mCircle; }
private:
    CircleComponent* mCircle;
};

#endif