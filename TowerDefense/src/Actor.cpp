#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"
#include <algorithm>

Actor::Actor(Game* game)
    :   mGame(game),
        mState(EActive),
        mScale(1.0f),
        mRotation(0.0f)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    while(!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if(mState == EActive || mState == EReborn)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for(auto component : mComponents)
    {
        component->Update(deltaTime);
    }
}

void Actor::ProcessInput(const uint8_t* keyState)
{
    if(mState == EActive)
    {
        for(auto component : mComponents)
        {
            component->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::AddComponents(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for(; iter != mComponents.end(); iter++)
    {
        if(myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    mComponents.insert(iter, component);
}

void Actor::RemoveComponents(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if(iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}
