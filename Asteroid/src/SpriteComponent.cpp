#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    :   Component(owner),
        mDrawOrder(drawOrder),
        mTexture(nullptr),
        mTexWidth(0),
        mTexHeight(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
    if(mTexture && mOwner->GetState() == Actor::EActive)
    {
        SDL_Rect r;

        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
        r.x = static_cast<int>(mOwner->GetPosition().x - (r.w/2.0f));
        r.y = static_cast<int>(mOwner->GetPosition().y - (r.h/2.0f));

        double rotation = -Math::ToDegrees(mOwner->GetRotation());

        SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, rotation, nullptr, SDL_FLIP_NONE);
    }
}


void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;

    // Get width/height of texture
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

