#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"
#include <algorithm>

Actor::Actor(Game* game)
    :   mGame(game),
        mState(EActive),
        mRecomputeWorldTransform(true)
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
        ComputeWorldTransform();
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
        ComputeWorldTransform();
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

void Actor::ComputeWorldTransform()
{
    if(mRecomputeWorldTransform)
    {
        mRecomputeWorldTransform = false;

        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));
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
