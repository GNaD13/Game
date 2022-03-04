#include "Grid.hpp"
#include "Game.hpp"
#include "Tile.hpp"
#include <algorithm>
#include <iostream>


Grid::Grid(Game* game)
    :   Actor(game),
        mSelectedTile(nullptr)
{
    // Load Tile
    mTiles.resize(NumRows);
    for(size_t i = 0; i < NumRows; i++)
    {
        mTiles[i].resize(NumCols);
    }

    for(size_t i = 0; i < NumRows; i++)
    {
        for(size_t j = 0; j < NumCols; j++)
        {
            mTiles[i][j] = new Tile(GetGame());
            mTiles[i][j]->SetPosition(Vector2(TileSize/2.0f + j * TileSize, StartY + i * TileSize));
            mTiles[i][j]->SetRotation(0.0f);
            mTiles[i][j]->SetScale(1.0f);
        }
    }

    // Set Adjacency List
    for(size_t i = 0; i < NumRows; i++)
    {
        for(size_t j = 0; j < NumCols; j++)
        {
            if(i > 0)
            {
                mTiles[i][j]->AddAdjacency(mTiles[i - 1][j]);
            }
            if(i < NumRows - 1)
            {
                mTiles[i][j]->AddAdjacency(mTiles[i + 1][j]);
            }
            if(j > 0)
            {
                mTiles[i][j]->AddAdjacency(mTiles[i][j - 1]);
            }
            if(j < NumCols - 1)
            {
                mTiles[i][j]->AddAdjacency(mTiles[i][j + 1]);
            }
        }
    }

    // // Set Start and Goal Point
    GetStartTile()->SetTileState(Tile::TileState::EStart);
    GetEndTile()->SetTileState(Tile::TileState::EGoal);

    // // Update Path from Start to Goal
    bool temp = FindPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());

    // Set enemytime
    mNextEnemy = EnemyTime;
}

Grid::~Grid()
{

}

void Grid::ProcessClick(int x, int y)
{

}

bool Grid::FindPath(Tile* start, Tile* goal)
{
    // Set up
    for(size_t i = 0; i < NumRows; i++)
    {
        for(size_t j = 0; j < NumCols; j++)
        {
            if(mTiles[i][j]->GetTileState() != Tile::TileState::EStart && 
                mTiles[i][j]->GetTileState() != Tile::TileState::EGoal)
            {
                mTiles[i][j]->f = 0.0f;
                mTiles[i][j]->mInCloseSet = false;
                mTiles[i][j]->mInOpenSet = false;
            }
        }
    }

    std::vector<Tile*> openSet;

    Tile* currentTile = start;
    currentTile->mInCloseSet = true;

    do
    {
        // consider adjcency of current tile
        for(auto adj : currentTile->mAdjacencyTile)
        {
            // Check if block
            if(adj->mBlocked)
            {
                continue;
            }
            // Only check if aren't in close set
            if(!adj->mInCloseSet)
            {
                // check if aren't in open set
                if(!adj->mInOpenSet)
                {
                    adj->mParent = currentTile;
                    adj->g = currentTile->g + TileSize;
                    adj->h = Vector2(GetEndTile()->GetPosition() - adj->GetPosition()).Length();
                    adj->f = adj->g + adj->h;
                    adj->mInOpenSet = true;
                    openSet.push_back(adj);
                }
                // check if in open set calculate new g
                else
                {
                    float newG = currentTile->g + TileSize;
                    if(newG < adj->g)
                    {
                        adj->mParent = currentTile;
                        adj->g = newG;
                        adj->f = adj->g + adj->h;
                    }
                }
            }
        }

        if(openSet.empty())
        {
            break;
        }

        auto iter = std::min_element(openSet.begin(), openSet.end(), [](Tile* a, Tile* b){
            return a->f < b->f;
        });

        currentTile = *iter;
        openSet.erase(iter);;
        currentTile->mInOpenSet = false;
        currentTile->mInCloseSet = true;

    } while (currentTile != goal);

    return currentTile == goal;
}

void Grid::SelectTile(size_t row, size_t col)
{
    Tile::TileState state = mTiles[row][col]->GetTileState();
    if(state != Tile::TileState::EStart && state != Tile::TileState::EGoal)
    {
        if(mSelectedTile != mTiles[row][col])
        {
            UnSelectTile();
            mSelectedTile = mTiles[row][col];
            mSelectedTile->ToggleSelect();
        }
        else
        {
            UnSelectTile();
        }
    }
}

void Grid::UnSelectTile()
{
    if(mSelectedTile)
    {
        mSelectedTile->ToggleSelect();
        mSelectedTile = nullptr;
    }
}

void Grid::UpdatePathTiles(Tile* start)
{
    // Reset map
    for(size_t i = 0; i < NumRows; i++)
    {
        for(size_t j = 0; j < NumCols; j++)
        {
            if(mTiles[i][j]->GetTileState() != Tile::TileState::EStart && mTiles[i][j]->GetTileState() != Tile::TileState::EGoal)
            {
                mTiles[i][j]->SetTileState(Tile::TileState::EDefault);
            }
        }
    }

    // Set path
    Tile* t = start->mParent;
    while(t != GetEndTile())
    {
        t->SetTileState(Tile::TileState::EPath);
        t = t->mParent;
    }
}

void Grid::BuildTower()
{

}

Tile* Grid::GetStartTile()
{
    return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
    return mTiles[1][15];
}

void Grid::UpdateActor(float deltaTime)
{
    mNextEnemy -= deltaTime;
    if(mNextEnemy <= 0.0f)
    {
        
    }
}