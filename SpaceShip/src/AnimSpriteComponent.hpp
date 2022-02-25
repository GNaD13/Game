#ifndef AnimSpriteComponent_hpp
#define AnimSpriteComponent_hpp

#include "SpriteComponent.hpp"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(Actor* owner, int drawOrder = 100);
    ~AnimSpriteComponent();

    virtual void Update(float deltaTime) override;

    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

    void SetAnimFPS(float fps) { mAnimFPS = fps; }
    float GetAnimFPS() { return mAnimFPS; }
private:
    std::vector<SDL_Texture*> mAnimTextures;
    float mCurrentFrame;
    float mAnimFPS;
};

#endif