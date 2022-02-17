#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <SDL2/SDL.h>

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

    void AddSprite();
    void RemoveSprite();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
// member variable
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    uint32_t mTickCount;

    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    bool mIsUpdatingActors;

    bool mIsRunning;
};

#endif