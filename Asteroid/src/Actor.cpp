#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"

Actor::Actor(Game* game)
    : mGame(game)
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
    UpdateComponents(deltaTime);
    UpdateActor(deltaTime);
}

void Actor::UpdateComponents(float deltaTime)
{
    for(auto component : mComponents)
    {
        component->Update(deltaTime);
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

}
