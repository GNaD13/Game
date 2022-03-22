#include "Game.hpp"
#include "Actor.hpp"
#include <algorithm>
#include "Renderer.hpp"
#include "MeshComponent.hpp"

Game::Game()
    : mTickCount(0)
    , mIsUpdatingActors(false)
    , mIsRunning(true)
{

}

Game::~Game()
{

}

bool Game::Initialize()
{
    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if(result != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    // Initialize SDL
    mRenderer = new Renderer(this);
    if(mRenderer->Initialize(1024.0f, 768.0f))
    {
        SDL_Log("Failed to initialize renderer");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }

    LoadData();

    mTickCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    UnloadData();
    if(mRenderer)
    {
        mRenderer->Shutdown();
    }
    SDL_Quit();
}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
        {
            mIsRunning = false;
            break;
        }
        default:
            break;
    }

    const uint8_t* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }

    mIsUpdatingActors = true;
    for(auto actor : mActors)
    {
        actor->ProcessInput(state);
    }
    mIsUpdatingActors = false;
}

void Game::UpdateGame()
{
    // Wait until 16ms has elapsed since last frame
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

    float deltaTime = static_cast<float>(SDL_GetTicks() - mTickCount) / 1000.0f;
    // Maximum delta time
    if(deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    // update tick count
    mTickCount = SDL_GetTicks();

    // Update Actor
    mIsUpdatingActors = true;
    for(auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mIsUpdatingActors = false;

    // Emplace pending actor to actor
    for(auto pending : mPendingActors)
    {
        pending->ComputeWorldTransform();
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // Delete dead actor
    std::vector<Actor*> deadActor;
    for(auto actor : mActors)
    {
        if(actor->GetState() == Actor::State::EDead)
        {
            deadActor.emplace_back(actor);
        }
    }

    for(auto actor : deadActor)
    {
        // Auto remove from Actors
        delete actor;
    }
}

void Game::GenerateOutput()
{
    if(mRenderer)
    {
        mRenderer->Draw();
    }
}

void Game::LoadData()
{
    // Actor* temp = new Actor(this);
    // SpriteComponent* sc = new SpriteComponent(temp);
    // sc->SetTexture(mRenderer->GetTexture("../Assets/Cube.png"));

    Actor* a = new Actor(this);
    a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
    a->SetScale(100.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    a->SetRotation(q);
    MeshComponent* mc = new MeshComponent(a);
    mc->SetMesh(mRenderer->GetMesh("../Assets/Cube.gpmesh"));

    a = new Actor(this);
    a->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
    a->SetScale(3.0f);
    mc = new MeshComponent(a);
    mc->SetMesh(mRenderer->GetMesh("../Assets/Sphere.gpmesh"));

    mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
}

void Game::UnloadData()
{
    while(!mActors.empty())
    {
        delete mActors.back();
    }

    if(mRenderer)
    {
        mRenderer->UnloadData();
    }
}

void Game::AddActor(Actor* actor)
{
    if(mIsUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    // Is actor in PendingActor?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if(iter != mPendingActors.end())
    {
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    // Is actor in Actor?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if(iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}