#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include "Grid.h"
#include "Texture.h"

// Screen dimension constants
inline const int SCREEN_WIDTH = 600;
inline const int SCREEN_HEIGHT = 600;

class Game
{
  public:
    void run();

  private:
    bool init();
    bool loadMedia();
    void close();

    void processEvents();
    void update();
    void render();

    // Helper Functions
    void AI();
    void CheckWin();
    void DrawGrids();
    void DrawPrimitive(int x, int y, int state);
    void DrawXO();

  private:
    // Game State
    bool mIsRunning = true;
    bool inputField[3][3] = {false, false, false, false, false, false, false, false, false};
    int gridState[3][3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int turn = 1;

    // Game Assets
    SDL_Window *mWindow = NULL;
    SDL_Renderer *mRenderer = NULL;
    SDL_Event e;
    SDL_Rect mSpriteClips[2];
    Texture mSpriteSheetTexture;
    Grid gridcheck[3][3] = {Grid(0, 0), Grid(0, 1), Grid(0, 2), Grid(1, 0), Grid(1, 1),
                            Grid(1, 2), Grid(2, 0), Grid(2, 1), Grid(2, 2)};
};

#endif // GAME_H