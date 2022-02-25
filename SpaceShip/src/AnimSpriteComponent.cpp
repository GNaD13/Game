#include "AnimSpriteComponent.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    :   SpriteComponent(owner, drawOrder),
        mCurrentFrame(0.0f),
        mAnimFPS(24.0f)
{

}

AnimSpriteComponent::~AnimSpriteComponent()
{

}

void AnimSpriteComponent::Update(float deltaTime)
{
    // SpriteComponent::Update(deltaTime);
    if(mAnimTextures.size() > 0)
    {
        mCurrentFrame += mAnimFPS * deltaTime;
        while(mCurrentFrame >= mAnimTextures.size())
        {
            mCurrentFrame -= mAnimTextures.size();
        }
        SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
    mAnimTextures = textures;

    if(mAnimTextures.size() != 0)
    {
        mCurrentFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}