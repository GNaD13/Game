#include "Game.hpp"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
    :   mWindow(nullptr),
        mRenderer(nullptr),
        mTickCount(0),
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
    mWindow = SDL_CreateWindow("Pong", 100, 100, 1024, 768, 0);
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

    mBallPos = { 1024.0f/2.0f, 768.0f/2.0f };
    mBallVel = { -200.0f, 235.0f };
    
    mPaddlePos = { 10.0f, 768.0f/2.0f };

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

    mPaddleDir = 0;
    if(state[SDL_SCANCODE_W])
    {
        mPaddleDir = -1;
    }
    if(state[SDL_SCANCODE_S])
    {
        mPaddleDir = 1;
    }
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
    
    // update paddle
    if(mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        // Top bound
        if(mPaddlePos.y < (paddleH/2.0f) + thickness)
        {
            mPaddlePos.y = (paddleH/2.0f) + thickness;
        }
        // Bottom bound
        if(mPaddlePos.y > (768.0f - (float)thickness - (paddleH/2.0f)))
        {
            mPaddlePos.y = (768.0f - (float)thickness - (paddleH/2.0f));
        }
    }

    //update ball
    mBallPos.x += (mBallVel.x * deltaTime);
    mBallPos.y += (mBallVel.y * deltaTime);
    
    // Lose game
    if(mBallPos.x < 0.0f)
    {
        mIsRunning = false;
    }

    // Collision bottom and top wall
    if(((mBallPos.y > 768.0f - thickness - (thickness / 2.0f)) && mBallVel.y > 0)
        || (mBallPos.y < thickness + (thickness / 2.0f)) && mBallVel.y < 0)
    {
        mBallVel.y *= -1;
    }

    // Collision right wall
    if((mBallPos.x > (1024.0f - thickness - (thickness / 2.0f)) && mBallVel.x > 0))
    {
        mBallVel.x *= -1;
    }

    // Collision paddle
    float diff = mBallPos.y - mPaddlePos.y;
    diff = diff > 0.0f ? diff : (-1.0f) * diff;
    if(diff <= paddleH / 2.0f && 
        mBallPos.x < 25.0f &&  mBallPos.x > 20.0f &&
        mBallVel.x < 0)
    {
        mBallVel.x *= -1;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 120, 100, 255);
    // Draw top wall
    SDL_Rect topWall
    {
        0,
        0,
        1024,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &topWall);
    // Draw right wall
    SDL_Rect rightWall
    {
        1024 - thickness,
        0,
        thickness,
        768
    };
    SDL_RenderFillRect(mRenderer, &rightWall);
    // Draw bottom wall
    SDL_Rect bottomWall
    {
        0,
        768 - thickness,
        1024,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &bottomWall);
    // Draw ball
    SDL_Rect ball
    {
        static_cast<int>(mBallPos.x - thickness/2),
        static_cast<int>(mBallPos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);
    // Draw Paddle
    SDL_Rect paddle
    {
        static_cast<int>(mPaddlePos.x - thickness/2),
        static_cast<int>(mPaddlePos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_RenderPresent(mRenderer);
}

