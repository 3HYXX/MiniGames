#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {

public:
  Window();
  ~Window();

  bool init();
  void run();
  void processEvents();

  // Creates renderer from internal window
  SDL_Renderer *createRenderer();

  void free();

  int getWidth();
  int getHeight();

  bool hasMouseFocus();
  bool hasKeyboardFocus();
  bool isMinimized();

private:
  void handleEvent(SDL_Event &e);

private:
  SDL_Window *mWindow;

  // Window dimensions
  int mWidth;
  int mHeight;

  // Window focus
  bool mMouseFocus;
  bool mKeyboardFocus;
  bool mFullScreen;
  bool mMinimized;
};

#endif // WINDOW_H