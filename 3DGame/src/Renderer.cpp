#include <algorithm>
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Game.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "MeshComponent.hpp"

Renderer::Renderer(Game* game)
    : mGame(game)
    , mSpriteShader(nullptr)
    , mMeshShader(nullptr)
{

}

Renderer::~Renderer()
{

}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;

    // Config OpenGL
    // Use the core OpenGL Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Specify version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Request a color buffer with 8 bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // Create Window
    mWindow = SDL_CreateWindow("SpaceShip", 100, 100, mScreenWidth, mScreenHeight, SDL_WINDOW_OPENGL);
    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create Context
    mContext = SDL_GL_CreateContext(mWindow);

    // Initial Glew
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        SDL_Log("Failed to initialize GLEW");
        return false;
    }

    glGetError();

    if(!LoadShaders())
    {
        SDL_Log("Failed to load shader");
        return false;
    }

    CreateSpriteVerts();
}

void Renderer::Shutdown()
{
    delete mSpriteVerts;
    mSpriteShader->Unload();
    delete mSpriteShader;
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
    for (auto i : mTextures)
	{
        i.second->Unload();
        delete i.second;
	}
	mTextures.clear();

    for (auto i : mMeshs)
	{
        i.second->Unload();
        delete i.second;
	}
	mMeshs.clear();
}

void Renderer::Draw()
{
    glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    mMeshShader->SetActive();
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
    SetLightUniforms(mMeshShader);
    for(auto mc : mMeshComps)
    {
        mc->Draw(mMeshShader);
    }

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mSpriteShader->SetActive();
    mSpriteVerts->SetActive();

    for(auto sprite : mSprites)
    {
        sprite->Draw(mSpriteShader);
    }

    SDL_GL_SwapWindow(mWindow);
}

bool Renderer::LoadShaders()
{

    // Create sprite shader
    mSpriteShader = new Shader();
    if(!mSpriteShader->Load("../Shader/BasicVert.glsl", "../Shader/BasicFrag.glsl"))
    {
        return false;
    }
    mSpriteShader->SetActive();

    Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.0f, 768.0f);
    mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

    // Create mesh shader 
    mMeshShader = new Shader();
    if(!mMeshShader->Load("../Shader/PhongVert.glsl", "../Shader/PhongFrag.glsl"))
    {
        return false;
    }
    mMeshShader->SetActive();
    mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

    return true;
}

void Renderer::CreateSpriteVerts()
{
    float verticies[] = {
        -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    mSpriteVerts = new VertexArray(verticies, 4, indicies, 6);
}

void Renderer::SetLightUniforms(Shader* shader)
{
    Matrix4 invView = mView;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    shader->SetVectorUniform("uAmbientLight", mAmbientLight);
    shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection);
    shader->SetVectorUniform("uDirLight.mDiffuseColor", mDirLight.mDiffuseColor);
    shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
    int myOrder = sprite->GetDrawOrder();
    auto iter = mSprites.begin();
    for(; iter != mSprites.end(); iter++)
    {
        if(myOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if(iter != mSprites.end())
    {
        mSprites.erase(iter);
    }
}

void Renderer::AddMeshComp(MeshComponent* mesh)
{
    mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent* mesh)
{
    auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
    if(iter != mMeshComps.end())
    {
        mMeshComps.erase(iter);
    }
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
    Texture* text = nullptr;
    auto iter = mTextures.find(fileName);
    if(iter != mTextures.end())
    {
        text = iter->second;
    }
    else
    {
        text = new Texture();
        if(text->Load(fileName))
        {
            mTextures.emplace(fileName, text);
            return text;
        }
        else
        {
            delete text;
            text = nullptr;
        }
    }
    return text;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
    Mesh* mesh = nullptr;
    auto iter = mMeshs.find(fileName);
    if(iter != mMeshs.end())
    {
        mesh = iter->second;
    }
    else
    {
        mesh = new Mesh();
        if(mesh->Load(fileName, this))
        {
            mMeshs.emplace(fileName, mesh);
            return mesh;
        }
        else
        {
            delete mesh;
            mesh = nullptr;
        }
    }
    return mesh;
}