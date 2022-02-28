#include "Laser.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"
#include "Asteroid.hpp"
#include <iostream>

Laser::Laser(Game* game)
    :   Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    SDL_Texture* text = GetGame()->GetTexture("../Assets/Laser.png");
    sc->SetTexture(text);

    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(800.0f);
    mc->SetAngularSpeed(0.0f);

    mCircle = new CircleComponent(this);
    mCircle->SetRadius(8.0f);

    mDeathTime = 10.0f;
}

Laser::~Laser()
{

}

void Laser::UpdateActor(float deltaTime)
{
    mDeathTime -= deltaTime;
    if(mDeathTime <= 0.0f)
        SetState(EDead);

    for(auto ast : GetGame()->GetAsteroid())
    {
        if(Intersect(*mCircle, *(ast->GetCircle())))
        {
            SetState(EDead);
            ast->SetState(EDead);
            break;
        }
    }
}