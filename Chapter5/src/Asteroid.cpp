#include "Asteroid.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"
#include "Random.h"

Asteroid::Asteroid(Game* game)
    :   Actor(game)
{
    Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f), Vector2(512.0f, 384.0f));
    float randRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
    SetPosition(randPos);
    SetScale(1.0f);
    SetRotation(randRotation);
    SetState(EActive);

    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(GetGame()->GetTexture("../Assets/Asteroid.png"));
    // SDL_Texture* text = GetGame()->GetTexture("../Assets/Asteroid.png");
    // sc->SetTexture(text);

    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(300.0f);
    mc->SetAngularSpeed(0.5f);

    mCircle = new CircleComponent(this);
    mCircle->SetRadius(40.0f);

    GetGame()->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
    GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
    Vector2 pos = GetPosition();
    if (pos.x < -512.0f) { pos.x = 510.0f; }
	else if (pos.x > 512.0f) { pos.x = -510.0f; }
	if (pos.y < -384.0f) { pos.y = 382.0f; }
	else if (pos.y > 384.0f) { pos.y = -382.0f; }
    SetPosition(pos);
}