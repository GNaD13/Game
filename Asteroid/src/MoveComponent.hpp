#ifndef MoveComponent_hpp
#define MoveComponent_hpp

#include "Component.hpp"

class MoveComponent : public Component
{
public:
    MoveComponent(Actor* owner, int updateOrder = 10);
    ~MoveComponent();

    virtual void Update(float deltaTime) override;

    void SetForwardSpeed(const float speed) { mForwardSpeed = speed; }
    float GetForwardSpeed() const { return mForwardSpeed; }

    void SetAngularSpeed(const float speed) { mAngularSpeed = speed; }
    float GetAngularSpeed() const { return mAngularSpeed; }
private:
    float mForwardSpeed;
    float mAngularSpeed;
};

#endif