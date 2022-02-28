#include "Asteroid.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Random.h"

Asteroid::Asteroid(Game* game)
    :   Actor(game)
{
    Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
    float randRotation = Random::GetFloatRange(0.0f, Math::TwoPi);
    SetPosition(randPos);
    SetScale(1.0f);
    SetRotation(randRotation);

    SpriteComponent* sprite = new SpriteComponent(this);
    SDL_Texture* text = GetGame()->GetTexture("../Assets/Asteroid.png");
    sprite->SetTexture(text);

    // MoveComponent* move = new MoveComponent(this);
    // move->SetForwardSpeed(100.0f);
    // move->SetAngularSpeed(30.0f);
}

Asteroid::~Asteroid()
{

}