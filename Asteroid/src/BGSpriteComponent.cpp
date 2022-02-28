#include "BGSpriteComponent.hpp"
#include "Actor.hpp"
#include <iostream>

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
    :   SpriteComponent(owner, drawOrder),
        mScrollSpeed(0.0f)
{

}

BGSpriteComponent::~BGSpriteComponent()
{

}

void BGSpriteComponent::Update(float deltaTime)
{
    for(auto& bg : mBGTextures)
    {
        bg.mOffset.x += mScrollSpeed * deltaTime;
        if(bg.mOffset.x < -mScreenSize.x)
        {
            bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
        }
        // std::cout << "-------------" << bg.mOffset.x << "-------------";
    }
    // std::cout << std::endl;
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
    for(auto& bg : mBGTextures)
    {
        SDL_Rect r;
        r.w = static_cast<int>(mScreenSize.x);
        r.h = static_cast<int>(mScreenSize.y);

        r.x = static_cast<int>((mOwner->GetPosition().x - r.w/2.0f) + bg.mOffset.x);
        r.y = static_cast<int>((mOwner->GetPosition().y - r.h/2.0f) + bg.mOffset.y);
        SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
    int count = 0;
    std::cout << "ScreenSize: " << mScreenSize.x << std::endl;

    for(auto tex : textures)
    {
        BGTexture temp;
        temp.mTexture = tex;

        temp.mOffset.x = count * mScreenSize.x;
        temp.mOffset.y = 0;
        mBGTextures.emplace_back(temp);
        count++;
        std::cout << "---------" << temp.mOffset.x << "---------";
    }
    std::cout << std::endl;
}