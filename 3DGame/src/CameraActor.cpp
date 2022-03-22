#include "CameraActor.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

CameraActor::CameraActor(Game* game)
    : Actor(game)
{
    mMoveComp = new MoveComponent(this);
}

CameraActor::~CameraActor()
{

}

void CameraActor::UpdateActor(float deltaTime)
{
    Vector3 pos = GetPosition();
    Vector3 target = GetPosition() + GetForward() * 100.0f;
    Vector3 up = Vector3::UnitZ;

    Matrix4 view = Matrix4::CreateLookAt(pos, target, up);
    GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const uint8_t* keyState)
{
    float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keyState[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keyState[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
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