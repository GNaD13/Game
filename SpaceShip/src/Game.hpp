#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unordered_map>
#include "SpriteComponent.hpp"
#include "Ship.hpp"

class Actor;

class Game
{
public:
    Game();
    ~Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    SDL_Texture* GetTexture(const std::string& filename);
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();
// member variable
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    uint32_t mTickCount;

    std::unordered_map<std::string, SDL_Texture*> mTextures;

    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    std::vector<SpriteComponent*> mSprites;
    bool mIsUpdatingActors;

    bool mIsRunning;

    Ship* mShip;
};

#endif