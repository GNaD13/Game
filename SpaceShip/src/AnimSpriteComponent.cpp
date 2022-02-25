#include "AnimSpriteComponent.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    :   SpriteComponent(owner, drawOrder),
        mCurrentFrame(0.0f),
        mAnimFPS(24.0f),
        mAnimFlag(AnimType::LOOPING)
{

}

AnimSpriteComponent::~AnimSpriteComponent()
{

}

void AnimSpriteComponent::Update(float deltaTime)
{
    // SpriteComponent::Update(deltaTime);
    if(mAnimFlag == AnimType::LOOPING)
    {
        if(mLoopingAnimTextures.size() > 0)
        {
            mCurrentFrame += mAnimFPS * deltaTime;
            while(mCurrentFrame >= mLoopingAnimTextures.size())
            {
                mCurrentFrame -= mLoopingAnimTextures.size();
            }
            SetTexture(mLoopingAnimTextures[static_cast<int>(mCurrentFrame)]);
        }
    }
    else if(mAnimFlag == AnimType::NONE_LOOPING)
    {
        if(mNoneLoopingAnimTextures.size() > 0)
        {
            mCurrentFrame += mAnimFPS * deltaTime;
            if(static_cast<int>(mCurrentFrame) >= mNoneLoopingAnimTextures.size())
            {
                mCurrentFrame = 0.0f;
                mNoneLoopingAnimTextures.clear();
                SetTexture(mLoopingAnimTextures[0]);
                mAnimFlag = AnimType::LOOPING;
                return;
            }
            SetTexture(mNoneLoopingAnimTextures[static_cast<int>(mCurrentFrame)]);
        }
    }
    
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures, AnimType type)
{
    mAnimFlag = type;
    if(mAnimFlag == AnimType::LOOPING)
    {
        if(mLoopingAnimTextures.size() != 0)
        {
            return;
        }
        mLoopingAnimTextures = textures;
        if(mLoopingAnimTextures.size() != 0)
        {
            mCurrentFrame = 0.0f;
            SetTexture(mLoopingAnimTextures[0]);
        }
    }
    else if(mAnimFlag == AnimType::NONE_LOOPING)
    {
        if(mNoneLoopingAnimTextures.size() != 0)
        {
            return;
        }
        mNoneLoopingAnimTextures = textures;
        if(mNoneLoopingAnimTextures.size() != 0)
        {
            mCurrentFrame = 0.0f;
            SetTexture(mNoneLoopingAnimTextures[0]);
        }
    }
    
}