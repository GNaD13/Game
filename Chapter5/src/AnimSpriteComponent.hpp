#ifndef AnimSpriteComponent_hpp
#define AnimSpriteComponent_hpp

#include "SpriteComponent.hpp"
#include <vector>
#include <unordered_map>

// class AnimSpriteComponent : public SpriteComponent
// {
// public:
//     enum class AnimType
//     {
//         LOOPING,
//         NONE_LOOPING
//     };

//     AnimSpriteComponent(Actor* owner, int drawOrder = 100);
//     ~AnimSpriteComponent();

//     virtual void Update(float deltaTime) override;

//     void SetAnimTextures(const std::vector<SDL_Texture*>& textures, AnimType type);

//     void SetAnimFPS(float fps) { mAnimFPS = fps; }
//     float GetAnimFPS() { return mAnimFPS; }
// private:
//     AnimType mAnimFlag;
//     std::vector<SDL_Texture*> mNoneLoopingAnimTextures;
//     std::vector<SDL_Texture*> mLoopingAnimTextures;
//     float mCurrentFrame;
//     float mAnimFPS;
// };

#endif