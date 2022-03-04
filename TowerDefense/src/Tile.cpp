#include "Tile.hpp"
#include "Game.hpp"
#include "SpriteComponent.hpp"

Tile::Tile(Game* game)
    :   Actor(game),
        mParent(nullptr),
        mBlocked(false),
        mTileState(TileState::EDefault),
        mSelected(false),
        f(0.0f), // f(x) = g(x) + h(x)
        g(0.0f),
        h(0.0f),
        mInOpenSet(false),
        mInCloseSet(false)
{
    mSprite = new SpriteComponent(this);
    UpdateTexture();
}

Tile::~Tile()
{

}

void Tile::ToggleSelect()
{
    mSelected = !mSelected;
    UpdateTexture();
}

void Tile::UpdateTexture()
{
    std::string text;
    switch (mTileState)
    {
        case TileState::EStart:
        {
            text = "../Assets/TileTanSelected.png";
            break;
        }
        case TileState::EGoal:
        {
            text = "../Assets/TileGreySelected.png";
            break;
        }
        case TileState::EPath:
        {
            if(mSelected)
            {
                text = "../Assets/TileBrownSelected.png";
            }
            else
            {
                text = "../Assets/TileBrown.png";
            }
            break;
        }
        case TileState::EDefault:
        {
            if(mSelected)
            {
                text = "../Assets/TileGreenSelected.png";
            }
            else
            {
                text = "../Assets/TileGreen.png";
            }
            break;
        }
        default:
        {
            text = "../Assets/TileGreen.png";
            break;
        }
    }
    mSprite->SetTexture(GetGame()->GetTexture(text));
}