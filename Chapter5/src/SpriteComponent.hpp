#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include <SDL2/SDL.h>

class Shader;
class Texture;

class SpriteComponent : public Component
{
public:
    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(Shader* shader);
    virtual void SetTexture(Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexWidth() const { return mTexWidth; }
    int GetTexHeight() const { return mTexHeight; }

protected:
    Texture* mTexture;
    int mDrawOrder;

    int mTexWidth;
    int mTexHeight;
};

#endif