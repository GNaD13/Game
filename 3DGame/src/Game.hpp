#ifndef Game_hpp
#define Game_hpp

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <unordered_map>
#include "SpriteComponent.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


class Renderer;
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

    Renderer* GetRenderer() { return mRenderer; }
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    uint32_t mTickCount;

    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    bool mIsUpdatingActors;

    Renderer* mRenderer;

    bool mIsRunning;
};

#endif