#include "Window.h"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Window::Window() {
  mWindow = NULL;
  mMouseFocus = false;
  mKeyboardFocus = false;
  mFullScreen = false;
  mMinimized = false;
  mWidth = 0;
  mHeight = 0;
}

bool Window::init() {
  // Create window
  mWindow = SDL_CreateWindow(
      "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (mWindow != NULL) {
    mMouseFocus = true;
    mKeyboardFocus = true;
    mWidth = SCREEN_WIDTH;
    mHeight = SCREEN_HEIGHT;
  }
  return mWindow != NULL;
}

void Window::run(){
    while(!mMinimized){
        processEvents();
    }
}

void Window::free() {
  if (mWindow != NULL) {
    SDL_DestroyWindow(mWindow);
  }

  mMouseFocus = false;
  mKeyboardFocus = false;
  mWidth = 0;
  mHeight = 0;
}
