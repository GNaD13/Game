#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
public:
    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexWidth() const { return mTexWidth; }
    int GetTexHeight() const { return mTexHeight; }

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;

    int mTexWidth;
    int mTexHeight;
};

#endif