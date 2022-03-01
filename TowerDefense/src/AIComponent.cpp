#include "AIComponent.hpp"
#include "Actor.hpp"
#include "AIState.hpp"
#include <algorithm>
#include <SDL2/SDL.h>

AIComponent::AIComponent(Actor* owner)
    :   Component(owner)
{

}

AIComponent::~AIComponent()
{

}

void AIComponent::Update(float deltaTime)
{
    if(mCurrentState)
    {
        mCurrentState->Update(deltaTime);
    }
}

void AIComponent::RegisterState(AIState* state)
{
    mStateMap.emplace(state->GetName(), state);
}

void AIComponent::ChangeState(const std::string& stateName)
{
    if(mCurrentState)
    {
        mCurrentState->OnExit();
    }

    auto iter = mStateMap.find(stateName);
    if(iter != mStateMap.end())
    {
        mCurrentState = iter->second;
        mCurrentState->OnEnter();
    }
    else
    {
        SDL_Log("Could not file state %s in state map", stateName.c_str());
        mCurrentState =  nullptr;
    }
}