#include "LightPointActor.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

LightPointActor::LightPointActor(Game* game)
    : Actor(game)
{
    mMoveComp = new MoveComponent(this);
}

LightPointActor::~LightPointActor()
{

}

void LightPointActor::UpdateActor(float deltaTime)
{
    DirectionalLight& dir = GetGame()->GetRenderer()->GetDirectionalLight();
    dir.mDirection = Vector3((-1) * GetPosition());
}

void LightPointActor::ActorInput(const uint8_t* keyState)
{
    float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 50.0f;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 50.0f;
	}
	if (keyState[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::TwoPi;
	}
	if (keyState[SDL_SCANCODE_D])
	{
		angularSpeed += Math::TwoPi;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}
