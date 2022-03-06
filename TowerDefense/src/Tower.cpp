#include "Tower.hpp"
#include "SpriteComponent.hpp"
#include "Game.hpp"

Tower::Tower(Game* game)
    :   Actor(game),
        mCoolDown(0.0f),
        mDelayTime(1.0f)
{
    mSprite = new SpriteComponent(this);
    mSprite->SetTexture(GetGame()->GetTexture("../Assets/Tower.png"));
}

Tower::~Tower()
{
    
}

void Tower::UpdateActor(float deltaTime)
{

}