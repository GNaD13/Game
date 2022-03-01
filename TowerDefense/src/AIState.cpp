#include "AIState.hpp"
#include "AIComponent.hpp"
#include <SDL2/SDL.h>

void AIPatrol::Update(float deltaTime)
{
    SDL_Log("Update %s state", GetName().c_str());
    mOwner->ChangeState("Death");
}

void AIPatrol::OnEnter()
{   SDL_Log("OnEnter %s state", GetName().c_str());

}

void AIPatrol::OnExit()
{
    SDL_Log("OnExit %s state", GetName().c_str());
}

void AIDeath::Update(float deltaTime)
{
    SDL_Log("Update %s state", GetName().c_str());
    mOwner->ChangeState("Patrol");
}

void AIDeath::OnEnter()
{
    SDL_Log("OnEnter %s state", GetName().c_str());
}

void AIDeath::OnExit()
{
    SDL_Log("OnExit %s state", GetName().c_str());
}