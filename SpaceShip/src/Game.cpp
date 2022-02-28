#include "Game.hpp"
#include "Actor.hpp"
#include <algorithm>
#include "BGSpriteComponent.hpp"
#include "Asteroid.hpp"

Game::Game()
    :   mWindow(nullptr),
        mRenderer(nullptr),
        mTickCount(0),
        mIsUpdatingActors(false),
        mIsRunning(true)
{

}

Game::~Game()
{

}

bool Game::Initialize()
{
    // Initialize SDL
    int result = SDL_Init(SDL_INIT_VIDEO);
    if(result != 0)
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Create Window
    mWindow = SDL_CreateWindow("SpaceShip", 100, 100, 1024, 768, 0);
    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Create Renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        SDL_Log("Failed to initialize IMG: %s", SDL_GetError());
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
    IMG_Quit();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}


//
// Internal Function
//
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

    mShip->ProcessInput(state);
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
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    for(auto sprite : mSprites)
    {
        sprite->Draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
    mShip = new Ship(this);
    mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);
    mShip->SetRotation(0);

    Asteroid* as = new Asteroid(this);
    as->SetPosition(Vector2(512.0f, 384.0f));
	as->SetScale(1.5f);
    as->SetRotation(0);

    // Actor* temp = new Actor(this);
    // temp->SetPosition(Vector2(512.0f, 384.0f));

    // // Set far back ground
    // BGSpriteComponent* bg = new BGSpriteComponent(temp);
    // bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    // std::vector<SDL_Texture*> bgText = { GetTexture("../Assets/Farback01.png"),
    //                                       GetTexture("../Assets/Farback02.png") };
    // bg->SetBGTextures(bgText);
    // bg->SetScrollSpeed(-100.0f);

    // bg = new BGSpriteComponent(temp, 50);
    // bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    // bgText = { GetTexture("../Assets/Stars.png"),
	// 	       GetTexture("../Assets/Stars.png")};
	// bg->SetBGTextures(bgText);
	// bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
    while(!mActors.empty())
    {
        delete mActors.back();
    }

    for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& filename)
{
    SDL_Texture* texture = nullptr;
    auto iter = mTextures.find(filename);
    if(iter != mTextures.end())
    {
        texture = iter->second;
        return texture;
    }
    else
    {
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if(!surf)
        {
            SDL_Log("Failed to load texture file %s", filename.c_str());
            return nullptr;
        }

        texture = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if(!texture)
        {
            SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
            return nullptr;
        }

        return texture;
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
    {
        auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
        if(iter != mPendingActors.end())
        {
            std::iter_swap(iter, mPendingActors.end() - 1);
            mPendingActors.pop_back();
        }
    }
    // Is actor in Actor?
    {
        auto iter = std::find(mActors.begin(), mActors.end(), actor);
        if(iter != mActors.end())
        {
            std::iter_swap(iter, mActors.end() - 1);
            mActors.pop_back();
        }
    }
}

void Game::AddSprite(SpriteComponent* sprite)
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

void Game::RemoveSprite(SpriteComponent* sprite)
{
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if(iter != mSprites.end())
    {
        mSprites.erase(iter);
    }
}

