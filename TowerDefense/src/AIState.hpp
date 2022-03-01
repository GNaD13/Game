#ifndef AIState_hpp
#define AIState_hpp

#include <string>

class AIComponent;

class AIState
{
public:
    AIState(AIComponent* owner)
        :   mOwner(owner)
    {}
    ~AIState() {}

    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;
    virtual const std::string GetName() const = 0;
protected:
    AIComponent* mOwner;
};

class AIPatrol : public AIState
{
public:
    AIPatrol(AIComponent* owner)
        :   AIState(owner)
    {}
    ~AIPatrol() {}
    
    virtual void Update(float deltaTime) override;
    virtual void OnEnter() override;
    virtual void OnExit() override;
    virtual const std::string GetName() const override { return "Patrol"; }
};

class AIDeath : public AIState
{
public:
    AIDeath(AIComponent* owner)
        :   AIState(owner)
    {}
    ~AIDeath() {}

    virtual void Update(float deltaTime) override;
    virtual void OnEnter() override;
    virtual void OnExit() override;
    virtual const std::string GetName() const override { return "Death"; }
};

#endif