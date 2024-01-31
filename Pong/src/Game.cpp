#include "Game.h"

#include "stdio.h"

#include <SDL_image.h>

void Game::run()
{
    if (!init())
    {
        printf("Failed to initialize!\n");
        mIsRunning = false;
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
            mIsRunning = false;
        }
    }

    //Game Loop
    while (mIsRunning)
    {
        processEvents();
        update();
        render();
    }
    close();
}

bool Game::init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {

            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        mWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (mWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
            if (mRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool Game::loadMedia()
{
    // Loading success flag
    bool success = true;

    if (!mSpriteSheetTexture.loadFromFile("resources/OX.png", mRenderer))
    {
        printf("Failed to load SpriteSheetTexture!\n");
        success = false;
    }
    else
    {
        mSpriteSheetTexture.setBlendMode(SDL_BLENDMODE_BLEND);
        // Set top left sprite
        mSpriteClips[0].x = 0;
        mSpriteClips[0].y = 0;
        mSpriteClips[0].w = 200;
        mSpriteClips[0].h = 200;

        // Set top right sprite
        mSpriteClips[1].x = 200;
        mSpriteClips[1].y = 0;
        mSpriteClips[1].w = 200;
        mSpriteClips[1].h = 200;
    }

    return success;
}

void Game::close()
{
    // Free loaded images
    mSpriteSheetTexture.free();

    // Destroy window
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void Game::processEvents()
{

}

void Game::update()
{
 
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 54, 44, 51, 0xFF);
    SDL_RenderClear(mRenderer);



    // Update screen
    SDL_RenderPresent(mRenderer);
}
