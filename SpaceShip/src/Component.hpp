#ifndef Component_hpp
#define Component_hpp

class Actor;

class Component
{
public:
    Component(Actor* owner, int updateOrder = 100);
    virtual ~Component();

    virtual void Update(float deltaTime) {};
    int GetUpdateOrder() const { return mUpdateOrder; }
private:
// Owning Actor
    Actor* mOwner;
    int mUpdateOrder;
};

#endif