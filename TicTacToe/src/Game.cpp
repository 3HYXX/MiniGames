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
    // Clear InputField
    for (int i = 0; i < 9; i++)
    {
        inputField[i / 3][i % 3] = false;
    }
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        // User requests quit
        if (e.type == SDL_QUIT)
        {
            mIsRunning = false;
        }
        else
        {
            for (int i = 0; i < 9; ++i)
            {
                if(gridcheck[i / 3][i % 3].handleEvent(&e))
                {
                    inputField[i / 3][i % 3] = true;
                }
            }
        }
    }
}

void Game::update()
{
    if (turn % 2 != 0)
    {
        for (int i = 0; i < 9; i++)
        {
            if (inputField[i / 3][i % 3])
            {
                if (gridState[i / 3][i % 3] == 0)
                {
                    gridState[i / 3][i % 3] = 2;
                    turn++;
                    printf("AI's turn\n");
                    break;
                }
            }
        }
    }
    else
    {
        AI();
    }

    CheckWin();
}

void Game::render()
{
    SDL_SetRenderDrawColor(mRenderer, 54, 44, 51, 0xFF);
    SDL_RenderClear(mRenderer);

    DrawGrids();

    DrawXO();

    // Update screen
    SDL_RenderPresent(mRenderer);
}

void Game::AI()
{
    while (true)
    {
        int x = rand() % 3;
        int y = rand() % 3;
        if (gridState[x][y] == 0)
        {
            gridState[x][y] = 1;
            turn++;
            printf("Player's turn\n");
            break;
        }
    }
}

void Game::CheckWin()
{
    // Check Horizontal
    for (int i = 0; i < 3; i++)
    {
        if (gridState[i][0] == gridState[i][1] && gridState[i][1] == gridState[i][2] && gridState[i][0] != 0)
        {
            if (gridState[i][0] == 1)
            {
                printf("AI wins\n");
            }
            else
            {
                printf("Player wins\n");
            }
            mIsRunning = false;
        }
    }
    // Check Vertical
    for (int i = 0; i < 3; i++)
    {
        if (gridState[0][i] == gridState[1][i] && gridState[1][i] == gridState[2][i] && gridState[0][i] != 0)
        {
            if (gridState[i][0] == 1)
            {
                printf("AI wins\n");
            }
            else
            {
                printf("Player wins\n");
            }
            mIsRunning = false;
        }
    }
    // Check Diagonal
    if (gridState[0][0] == gridState[1][1] && gridState[1][1] == gridState[2][2] && gridState[0][0] != 0)
    {
        if (gridState[0][0] == 1)
        {
            printf("AI wins\n");
        }
        else
        {
            printf("Player wins\n");
        }
        mIsRunning = false;
    }
    if (gridState[0][2] == gridState[1][1] && gridState[1][1] == gridState[2][0] && gridState[0][2] != 0)
    {
        if (gridState[0][2] == 1)
        {
            printf("AI wins\n");
        }
        else
        {
            printf("Player wins\n");
        }
        mIsRunning = false;
    }

    if (mIsRunning && turn == 10)
    {
        printf("Nobody Win!\n");
        mIsRunning = false;
    }
}

void Game::DrawGrids()
{
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(mRenderer, 200, 0, 200, 600);
    SDL_RenderDrawLine(mRenderer, 400, 0, 400, 600);
    SDL_RenderDrawLine(mRenderer, 0, 200, 600, 200);
    SDL_RenderDrawLine(mRenderer, 0, 400, 600, 400);
}

void Game::DrawPrimitive(int x, int y, int state)
{
    x = x * 200;
    y = y * 200;
    mSpriteSheetTexture.render(x, y, &mSpriteClips[state]);
}

void Game::DrawXO()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gridState[i][j] == 1)
            {

                DrawPrimitive(i, j, 0);
            }
            else if (gridState[i][j] == 2)
            {
                DrawPrimitive(i, j, 1);
            }
        }
    }
}