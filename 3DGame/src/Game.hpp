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

#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768


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

    Texture* GetTexture(const std::string& fileName);
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    bool LoadShader();
    void CreateSpriteVerts();
    void LoadData();
    void UnloadData();
// member variable
    SDL_Window* mWindow;
    SDL_GLContext mContext;
    uint32_t mTickCount;

    std::unordered_map<std::string, Texture*> mTextures;

    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    VertexArray* mSpriteVerts;
    Shader* mSpriteShader;

    std::vector<SpriteComponent*> mSprites;
    bool mIsUpdatingActors;

    bool mIsRunning;
};

#endif