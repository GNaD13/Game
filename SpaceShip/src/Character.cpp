#include "Character.hpp"
#include "AnimSpriteComponent.hpp"
#include "Game.hpp"

Character::Character(Game* game)
    :   Actor(game),
        mDownSpeed(0.0f),
        mRightSpeed(0.0f)
{
    mAnim = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> texture = { GetGame()->GetTexture("../Assets/Character01.png"),
                                        //   GetGame()->GetTexture("../Assets/Character02.png"),
                                        //   GetGame()->GetTexture("../Assets/Character03.png"),
                                        //   GetGame()->GetTexture("../Assets/Character04.png"),
                                        //   GetGame()->GetTexture("../Assets/Character05.png"),
                                        //   GetGame()->GetTexture("../Assets/Character06.png") 
                                          };
    mAnim->SetAnimTextures(texture, AnimSpriteComponent::AnimType::LOOPING);
}

Character::~Character()
{

}

void Character::UpdateActor(float deltaTime)
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

void Character::ProcessInput(const uint8_t* state)
{
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;

    if(state[SDL_SCANCODE_W])
    {
        SetAnimWalk();
        mDownSpeed -= 250.0f;
    }

    if(state[SDL_SCANCODE_S])
    {
        SetAnimWalk();
        mDownSpeed += 250.;
    }

    if(state[SDL_SCANCODE_A])
    {
        SetAnimWalk();
        mRightSpeed -= 300.0f;
    }

    if(state[SDL_SCANCODE_D])
    {
        SetAnimWalk();
        mRightSpeed += 300.0f;
    }

    if(state[SDL_SCANCODE_SPACE])
    {
        SetAnimJump();
    }

    if(state[SDL_SCANCODE_J])
    {
        SetAnimPunch();
    }
}

void Character::SetAnimJump()
{
    std::vector<SDL_Texture*> texture = { GetGame()->GetTexture("../Assets/Character07.png"),
                                          GetGame()->GetTexture("../Assets/Character08.png"),
                                          GetGame()->GetTexture("../Assets/Character09.png"),
                                          GetGame()->GetTexture("../Assets/Character10.png"),
                                          GetGame()->GetTexture("../Assets/Character11.png"),
                                          GetGame()->GetTexture("../Assets/Character12.png"),
                                          GetGame()->GetTexture("../Assets/Character13.png"),
                                          GetGame()->GetTexture("../Assets/Character14.png"),
                                          GetGame()->GetTexture("../Assets/Character15.png")
                                        };
    mAnim->SetAnimTextures(texture, AnimSpriteComponent::AnimType::NONE_LOOPING);
}

void Character::SetAnimPunch()
{
    std::vector<SDL_Texture*> texture = { GetGame()->GetTexture("../Assets/Character16.png"),
                                          GetGame()->GetTexture("../Assets/Character17.png"),
                                          GetGame()->GetTexture("../Assets/Character18.png") 
                                        };
    mAnim->SetAnimTextures(texture, AnimSpriteComponent::AnimType::NONE_LOOPING);
}

void Character::SetAnimWalk()
{
    std::vector<SDL_Texture*> texture = { GetGame()->GetTexture("../Assets/Character01.png"),
                                          GetGame()->GetTexture("../Assets/Character02.png"),
                                          GetGame()->GetTexture("../Assets/Character03.png"),
                                          GetGame()->GetTexture("../Assets/Character04.png"),
                                          GetGame()->GetTexture("../Assets/Character05.png"),
                                          GetGame()->GetTexture("../Assets/Character06.png") 
                                        };
    mAnim->SetAnimTextures(texture, AnimSpriteComponent::AnimType::NONE_LOOPING);
}

