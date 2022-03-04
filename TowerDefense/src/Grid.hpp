#ifndef Grid_hpp
#define Grid_hpp

#include "Actor.hpp"

class Tile;

class Grid : public Actor
{
public:
    Grid(Game* game);
    ~Grid();

    void ProcessClick(int x, int y);
    // A* finding path
    bool FindPath(Tile* start, Tile* goal);

    void BuildTower();

    Tile* GetStartTile();
    Tile* GetEndTile();

    void UpdateActor(float deltaTime) override;
private:
    //  Select specifi tile
    void SelectTile(size_t row, size_t col);
    void UnSelectTile();

    void UpdatePathTiles(Tile* start);

    Tile* mSelectedTile;

    std::vector<std::vector<Tile*>> mTiles;

    float mNextEnemy;

    const size_t NumRows = 7;
    const size_t NumCols = 16;

    const float StartY = 192.0f;
    const float TileSize = 64.0f;

    const float EnemyTime = 1.5f;
};

#endif