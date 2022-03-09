#ifndef BGSpriteComponent_hpp
#define BGSpriteComponent_hpp


#include "SpriteComponent.hpp"
#include <vector>
#include "Math.h"

// class BGSpriteComponent : public SpriteComponent
// {
// public:
//     BGSpriteComponent(Actor* owner, int drawUpdate = 10);
//     ~BGSpriteComponent();

//     virtual void Update(float deltaTime) override;
//     virtual void Draw(SDL_Renderer* renderer) override;

//     void SetBGTextures(const std::vector<SDL_Texture*>& textures);
//     void SetScreenSize(const Vector2& size) { mScreenSize = size; }
//     void SetScrollSpeed(float speed) { mScrollSpeed = speed; }

//     float GetScrollSpeed() const { return mScrollSpeed; }
// private:
//     struct BGTexture
//     {
//         SDL_Texture* mTexture;
//         Vector2 mOffset;
//     };
    
//     std::vector<BGTexture> mBGTextures;
//     Vector2 mScreenSize;
//     float mScrollSpeed;
// };


#endif
