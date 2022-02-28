#include "Asteroid.hpp"
#include "SpriteComponent.hpp"
#include "Game.hpp"

Asteroid::Asteroid(Game* game)
    :   Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(GetGame()->GetTexture("/media/dangvhb/DATA/dangVHbCode/GameProgC++/Game/Game/SpaceShip/Assets/Enemy01.png"));
}

Asteroid::~Asteroid()
{
    
}