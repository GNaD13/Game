#ifndef Laser_hpp
#define Laser_hpp

#include "Actor.hpp"

class CircleComponent;

class Laser : public Actor
{
public:
    Laser(Game* game);
    ~Laser();

    virtual void UpdateActor(float deltaTime) override;
    CircleComponent* GetCircle() const { return mCircle; }
private:
    CircleComponent* mCircle;
    float mDeathTime;
};

#endif