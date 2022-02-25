#include "Ship.hpp"
#include "Game.hpp"
#include "AnimSpriteComponent.hpp"

Ship::Ship(Game* game)
    :   Actor(game),
        mRightSpeed(0.0f),
        mDownSpeed(0.0f)
{
    AnimSpriteComponent* anim = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> textures = { GetGame()->GetTexture("../Assets/Ship01.png"),
                                           GetGame()->GetTexture("../Assets/Ship02.png"),
                                           GetGame()->GetTexture("../Assets/Ship03.png"),
                                           GetGame()->GetTexture("../Assets/Ship04.png") };
    anim->SetAnimTextures(textures, AnimSpriteComponent::AnimType::LOOPING);
}

Ship::~Ship()
{

}

void Ship::UpdateActor(float deltaTime)
{
    Vector2 pos = GetPosition();

    pos.x += mRightSpeed * deltaTime;
    if(pos.x < 48.0f)
    {
        pos.x = 48.0f;
    }
    if(pos.x > 976.0f)
    {
        pos.x = 976.0f;
    }

    pos.y += mDownSpeed * deltaTime;

    if(pos.y < 15.0f)
    {
        pos.y = 15.0f;
    }
    if(pos.y > 750.0f)
    {
        pos.y = 750.0f;
    }

    SetPosition(pos);
}

void Ship::ProcessInput(const uint8_t* state)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;

    if(state[SDL_SCANCODE_W])
    {
        mDownSpeed -= 250.0f;
    }

    if(state[SDL_SCANCODE_S])
    {
        mDownSpeed += 250.;
    }

    if(state[SDL_SCANCODE_A])
    {
        mRightSpeed -= 300.0f;
    }

    if(state[SDL_SCANCODE_D])
    {
        mRightSpeed += 300.0f;
    }
}