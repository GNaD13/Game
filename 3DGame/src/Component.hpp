#ifndef Component_hpp
#define Component_hpp

#include <stdint.h>

class Actor;

class Component
{
public:
    Component(Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime) {}
    virtual void ProcessInput(const uint8_t* keyState) {}
    int GetUpdateOrder() const { return mUpdateOrder; }
protected:
// Owning Actor
    Actor* mOwner;
    int mUpdateOrder;
};

#endif