#include "PlaneActor.hpp"
#include "Game.hpp"
#include "Renderer.hpp"
#include "MeshComponent.hpp"

PlaneActor::PlaneActor(Game* game)
    : Actor(game)
{
    SetScale(10.0f);
    MeshComponent* meshcomp = new MeshComponent(this);
    meshcomp->SetMesh(GetGame()->GetRenderer()->GetMesh("../Assets/Plane.gpmesh"));
}

PlaneActor::~PlaneActor()
{

}