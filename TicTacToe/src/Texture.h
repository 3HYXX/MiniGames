#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL.h>

//Texture wrapper class
class Texture
{
    public:
        //Initializes variables
        Texture();

        //Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool loadFromFile(  std::string path , SDL_Renderer * renderer);

        //Deallocates texture
        void free();

        //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set blending
        void setBlendMode( SDL_BlendMode blending );

        //Set alpha modulation
        void setAlpha( Uint8 alpha );
        
        //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;
        SDL_Renderer * mRenderer;
        //Image dimensions
        int mWidth;
        int mHeight;
};

#endif // TEXTURE_H