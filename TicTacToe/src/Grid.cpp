#include "Grid.h"

extern int gridState[3][3];
extern int turn;

Grid::Grid(int x, int y)
{
	_x = x;
    _y = y;
    setPosition(x*GRID_WIDTH, y*GRID_HEIGHT);

}

void Grid::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void Grid::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + GRID_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + GRID_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
            
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				break;
			
				case SDL_MOUSEBUTTONDOWN:
                    if (gridState[_x][_y] == 0) {
                        gridState[_x][_y] = turn%2 + 1;
                        turn++;
                    }
				break;
				
				case SDL_MOUSEBUTTONUP:
				break;
			}
		}
	}
}

