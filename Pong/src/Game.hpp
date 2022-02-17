#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>

struct Vector2
{
    float x;
    float y;
};

class Game
{
public:
    Game();
    ~Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
// member variable
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    uint32_t mTickCount;

    Vector2 mBallPos;
    Vector2 mBallVel;

    Vector2 mPaddlePos;
    int mPaddleDir;

    bool mIsRunning;
};

#endif