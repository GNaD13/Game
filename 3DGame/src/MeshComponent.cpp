#include "MeshComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

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
    if(mMesh)
    {
        // Set shader uniform
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        // Set texture
        Texture* text = mMesh->GetTexture(mTextureIndex);
        if(text)
        {
            text->SetActive();
        }
        //Set vertex array
        VertexArray* va = mMesh->GetVertexArray();
        if(va)
        {
            va->SetActive();
        }
        glDrawElements(GL_TRIANGLES, va->GetNumIndicies(), GL_UNSIGNED_INT, nullptr);
    }
}
