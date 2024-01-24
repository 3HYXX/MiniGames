#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "Grid.h"
#include "Texture.h"

// Screen dimension constants
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

SDL_Rect gSpriteClips[2];
Texture gSpriteSheetTexture;

// Game Variables

// clang-format off
int gridState[3][3] = {0 , 0 , 0,
                  0 , 0 , 0,
                  0 , 0 , 0};

int debugState[3][3] = {
    1, 2, 2,
    2, 1, 1,
    1, 2, 2
};


Grid gridcheck[3][3] = {Grid(0, 0), Grid(0, 1), Grid(0, 2),
                        Grid(1, 0), Grid(1, 1), Grid(1, 2),
                        Grid(2, 0), Grid(2, 1), Grid(2, 2)};
// clang-format on

int turn = 1;

// Game Functions

void CheckWin()
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
            exit(0);
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
            exit(0);
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
        exit(0);
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
        exit(0);
    }

    bool drawout = true;
    for (int i = 0; i < 9; i++)
    {
        if (gridState[i / 3][i % 3] == 0)
        {
            drawout = false;
        }
    }
    if (drawout)
    {
        printf("Nobody Win!\n");
        exit(0);
    }
}

void AI()
{
    printf("AI's turn\n");
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

void DrawGrids()
{
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(gRenderer, 200, 0, 200, 600);
    SDL_RenderDrawLine(gRenderer, 400, 0, 400, 600);
    SDL_RenderDrawLine(gRenderer, 0, 200, 600, 200);
    SDL_RenderDrawLine(gRenderer, 0, 400, 600, 400);
}

void DrawO(int x, int y)
{
    x = x * 200;
    y = y * 200;
    gSpriteSheetTexture.render(x, y, &gSpriteClips[0]);
}

void DrawX(int x, int y)
{
    x = x * 200;
    y = y * 200;
    gSpriteSheetTexture.render(x, y, &gSpriteClips[1]);
}

void DrawXO()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gridState[i][j] == 1)
            {

                DrawO(i, j);
            }
            else if (gridState[i][j] == 2)
            {
                DrawX(i, j);
            }
        }
    }
}

int main(int argc, char *args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // Game Loop
            while (!quit)
            {
                CheckWin();

                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    // Handle key presses
                    else if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_w)
                        {
                            for (int i = 0; i < 3; i++)
                            {
                                for (int j = 0; j < 3; j++)
                                {
                                    gridState[i][j] = debugState[i][j];
                                }
                            }
                        }
                    }
                    else if (turn % 2 != 0)
                    {
                        for (int i = 0; i < 9; ++i)
                        {
                            gridcheck[i / 3][i % 3].handleEvent(&e);
                        }
                    }
                    else
                    {
                        AI();
                    }
                }

                // Render()
                //  Clear screen
                SDL_SetRenderDrawColor(gRenderer, 54, 44, 51, 0xFF);
                SDL_RenderClear(gRenderer);

                DrawGrids();

                DrawXO();

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}

bool init()
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
        gWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                   SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

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

bool loadMedia()
{
    // Loading success flag
    bool success = true;

    if (!gSpriteSheetTexture.loadFromFile("resources/OX.png"))
    {
        printf("Failed to load SpriteSheetTexture!\n");
        success = false;
    }
    else
    {
        gSpriteSheetTexture.setBlendMode(SDL_BLENDMODE_BLEND);
        // Set top left sprite
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 200;
        gSpriteClips[0].h = 200;

        // Set top right sprite
        gSpriteClips[1].x = 200;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 200;
        gSpriteClips[1].h = 200;
    }

    return success;
}

void close()
{
    // Free loaded images
    gSpriteSheetTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}