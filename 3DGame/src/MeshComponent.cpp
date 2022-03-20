#include "MeshComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"

MeshComponent::MeshComponent(Actor* owner)
    : Component(owner)
    , mMesh(nullptr)
    , mTextureIndex(0)
{
    mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
    mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
{

}

void MeshComponent::SetMesh(Mesh* mesh)
{

}

void MeshComponent::SetTextureIndex(size_t index)
{

}
