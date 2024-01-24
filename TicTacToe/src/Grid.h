#pragma once
#ifndef GRID_H
#define GRID_H

#include <SDL.h>

inline const int GRID_WIDTH = 200;
inline const int GRID_HEIGHT = 200;

class Grid
{
	public:
		//Initializes internal variables
		Grid(int x, int y);

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

	private:
		//Top left position
		SDL_Point mPosition;
        int _x;
        int _y;

};

#endif // GRID_H
