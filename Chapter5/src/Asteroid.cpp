#include "Asteroid.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"
#include "Random.h"

Asteroid::Asteroid(Game* game)
    :   Actor(game)
{
    Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
    float randRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
    SetPosition(randPos);
    SetScale(1.0f);
    SetRotation(randRotation);
    SetState(EActive);

    // SpriteComponent* sc = new SpriteComponent(this);
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
    pos.x = ((static_cast<int>(pos.x) + SCREEN_WIDTH) % SCREEN_WIDTH);
    pos.y = ((static_cast<int>(pos.y) + SCREEN_HEIGHT) % SCREEN_HEIGHT);
    SetPosition(pos);
}