#ifndef Tile_hpp
#define Tile_hpp

#include "Actor.hpp"
#include <iostream>

class SpriteComponent;

class Tile : public Actor
{
public:
    friend class Grid;
    enum class TileState
    {
        EDefault,
        EStart,
        EPath,
        EGoal
    };

    Tile(Game* game);
    ~Tile();

    void ToggleSelect();

    const TileState& GetTileState() const { return mTileState; }
    void SetTileState(TileState state) 
    { 
        mTileState = state;
        UpdateTexture();
    }

    Tile* GetParentTile() const { return mParent; }
    void SetParentTile(Tile* tile) { mParent = tile; }

    void AddAdjacency(Tile* tile) { mAdjacencyTile.push_back(tile); }
    const std::vector<Tile*>& GetAdjacency() const { return mAdjacencyTile; }

private:
    void UpdateTexture();

    TileState mTileState;

    // A* search variable
    std::vector<Tile*> mAdjacencyTile;
    Tile* mParent;
    float f; // f(x) = g(x) + h(x)
    float g;
    float h;
    bool mInOpenSet;
    bool mInCloseSet;

    SpriteComponent* mSprite;
    bool mSelected;
    bool mBlocked;
};

#endif