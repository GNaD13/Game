#include "Ship.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"
#include "Laser.hpp"
#include "CircleComponent.hpp"

Ship::Ship(Game* game)
    :   Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(GetGame()->GetTexture("../Assets/Ship.png"));

    InputComponent* ic = new InputComponent(this);
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockWiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockWiseKey(SDL_SCANCODE_D);

    ic->SetMaxForwardSpeed(150.0f);
    ic->SetMaxAngularSpeed(Math::TwoPi);

    mCircle = new CircleComponent(this);
    mCircle->SetRadius(40.0f);
    
    mCooldown = 0.0f;
    mReborn = 0.0f;
}

Ship::~Ship()
{

}

void Ship::UpdateActor(float deltaTime)
{
    mCooldown -= deltaTime;
    if(GetState() == EReborn)
    {
        mReborn += deltaTime;
        if(mReborn >= 2.0f)
        {
            SetPosition(Vector2(0.0f, 0.0f));
            SetRotation(0.0f);
            SetState(EActive);
        }
    }
    else if(GetState() == EActive)
    {
        // for(auto ast : GetGame()->GetAsteroid())
        // {
        //     if(Intersect(*mCircle, *(ast->GetCircle())))
        //     {
        //         SetState(EReborn);
        //         ast->SetState(EDead);
        //         mReborn = 0.0f;
        //         break;
        //     }

        // }
    }
}

void Ship::ActorInput(const uint8_t* keyState)
{
    if(keyState[SDL_SCANCODE_SPACE] && mCooldown <= 0.0f)
    {
        Laser* laser = new Laser(GetGame());
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());
        laser->SetScale(1.0f);
        mCooldown = 0.5f;
    }
}