#include "Game.hpp"
#include "Actor.hpp"
#include <algorithm>
// #include "BGSpriteComponent.hpp"
#include "Asteroid.hpp"

Game::Game()
    :   mWindow(nullptr),
        // mRenderer(nullptr),
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

    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // Create Window
    mWindow = SDL_CreateWindow("SpaceShip", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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

    // Create Renderer
    // mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if(!mRenderer)
    // {
    //     SDL_Log("Failed to create renderer: %s", SDL_GetError());
    //     return false;
    // }

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
    // SDL_DestroyRenderer(mRenderer);
    SDL_GL_DeleteContext(mContext);
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
    // SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    // SDL_RenderClear(mRenderer);

    // for(auto sprite : mSprites)
    // {
    //     sprite->Draw(mRenderer);
    // }

    // SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
    // mShip = new Ship(this);

    // const int numAsteroids = 20;
    // for(int i = 0; i < numAsteroids; i++)
    // {
    //     new Asteroid(this);
    // }
    
    // Actor* temp = new Actor(this);

    // temp->SetPosition(Vector2(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2));
    // temp->SetRotation(0.0f);

    // BGSpriteComponent* bg = new BGSpriteComponent(temp);
    // bg->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
    // std::vector<SDL_Texture*> tex = { GetTexture("../Assets/Farback01.png"),
    //                                   GetTexture("../Assets/Farback02.png")
    //                                 };
    // bg->SetBGTextures(tex);
    // bg->SetScrollSpeed(-100.0f);

    // bg = new BGSpriteComponent(temp, 20);
    // bg->SetScreenSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
    // tex = { GetTexture("../Assets/Stars.png"),
    //         GetTexture("../Assets/Stars.png")
    //       };
    // bg->SetBGTextures(tex);
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
    // SDL_Texture* texture = nullptr;
    // auto iter = mTextures.find(filename);
    // if(iter != mTextures.end())
    // {
    //     texture = iter->second;
    // }
    // else
    // {
    //     SDL_Surface* surf = IMG_Load(filename.c_str());
    //     if(!surf)
    //     {
    //         SDL_Log("Failed to load texture file %s", filename.c_str());
    //         return nullptr;
    //     }

    //     texture = SDL_CreateTextureFromSurface(mRenderer, surf);
    //     SDL_FreeSurface(surf);
    //     if(!texture)
    //     {
    //         SDL_Log("Failed to convert surface to texture for %s", filename.c_str());
    //         return nullptr;
    //     }
    //     mTextures.emplace(filename.c_str(), texture);
    // }
    // return texture;
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

// void Game::AddSprite(SpriteComponent* sprite)
// {
    // int myOrder = sprite->GetDrawOrder();
    // auto iter = mSprites.begin();
    // for(; iter != mSprites.end(); iter++)
    // {
    //     if(myOrder < (*iter)->GetDrawOrder())
    //     {
    //         break;
    //     }
    // }
    // mSprites.insert(iter, sprite);
// }

// void Game::RemoveSprite(SpriteComponent* sprite)
// {
//     auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
//     if(iter != mSprites.end())
//     {
//         mSprites.erase(iter);
//     }
// }

void Game::AddAsteroid(Asteroid* ast)
{
    mAsteroid.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
    auto iter = std::find(mAsteroid.begin(), mAsteroid.end(), ast);
    if(iter != mAsteroid.end())
    {
        mAsteroid.erase(iter);
    }
}

