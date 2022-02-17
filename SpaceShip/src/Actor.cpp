#include "Actor.hpp"
#include "Game.hpp"

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
