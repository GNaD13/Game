#ifndef AIComponent_hpp
#define AIComponent_hpp

#include "Component.hpp"
#include <string>
#include <unordered_map>

class AIState;

class AIComponent : public Component
{
public:
    AIComponent(Actor* owner);
    ~AIComponent();

    virtual void Update(float deltaTime) override;

    void ChangeState(const std::string& stateName);
    void RegisterState(AIState* state);
private:
    std::unordered_map<std::string, AIState*> mStateMap;
    AIState* mCurrentState;
};

#endif