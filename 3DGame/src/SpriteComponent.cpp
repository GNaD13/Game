#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Shader.hpp"
#include <iostream>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    :   Component(owner),
        mDrawOrder(drawOrder),
        mTexture(nullptr),
        mTexWidth(64),
        mTexHeight(64)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
    Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth), static_cast<float>(mTexHeight), 1.0f);
    Matrix4 worldTransMat = scaleMat * mOwner->GetWorldTransform();

    shader->SetMatrixUniform("uWorldTransform", worldTransMat);

    mTexture->SetActive();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}


void SpriteComponent::SetTexture(Texture* texture)
{
    mTexture = texture;
    mTexWidth = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}

