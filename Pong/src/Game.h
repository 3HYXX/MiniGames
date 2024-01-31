#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>

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

  private:
    // Game State
    bool mIsRunning = true;

    // Game Assets
    SDL_Window *mWindow = NULL;
    SDL_Renderer *mRenderer = NULL;
    SDL_Event e;
    SDL_Rect mSpriteClips[2];
    Texture mSpriteSheetTexture;
};

#endif // GAME_H