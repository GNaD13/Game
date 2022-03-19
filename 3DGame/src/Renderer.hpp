#ifndef Renderer_hpp
#define Renderer_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "Math.h"

class Game;
class SpriteComponent;
class MeshComponent;
class Mesh;
class Texture;
class Shader;
class VertexArray;

struct DirectionalLight
{
    // Direction of the light
    Vector3 mDirection;
    // Diffuse Color
    Vector3 mDiffuseColor;
    // Specular Color
    Vector3 mSpecColor;
};

class Renderer
{
public:
    Renderer(Game* game);
    ~Renderer();

    bool Initialize(float screenWidth, float screenHeight);
    void Shutdown();
    void UnloadData();

    void Draw();

    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);

    void AddMeshComp(MeshComponent* mesh);
    void RemoveMeshComp(MeshComponent* mesh);

    Texture* GetTexture(const std::string& fileName);
    Mesh* GetMesh(const std::string& fileName);

    float GetScreenWidth() const { return mScreenWidth; }
    float GetScreenHeight() const { return mScreenHeight; }
private:
    bool LoadShaders();
    void CreateSpriteVerts();
    // Map of texture/mesh
    std::unordered_map<std::string, Texture*> mTextures;
    std::unordered_map<std::string, Mesh*> mMeshs;

    // Sprite/Mesh component
    std::vector<SpriteComponent*> mSprites;
    std::vector<MeshComponent*> mMeshComps;

    // Game
    Game* mGame;

    // Renderer Component
    VertexArray* mSpriteVerts;
    Shader* mSpriteShader;
    Shader* mMeshShader;

    // View/projection for 3D
    Matrix4 mView;
    Matrix4 mProjection;

    // Width/Height of screen
    float mScreenWidth;
    float mScreenHeight;

    // Window
    SDL_Window* mWindow;
    //OpenGL Context
    SDL_GLContext mContext;
};

#endif