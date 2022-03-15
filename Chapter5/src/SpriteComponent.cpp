#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Shader.hpp"

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

void SpriteComponent::Draw(Shader* shader)
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


void SpriteComponent::SetTexture(SDL_Texture* texture)
{
    mTexture = texture;

    // Get width/height of texture
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

