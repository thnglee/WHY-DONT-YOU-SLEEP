#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
class LTexture
{
     public:
       LTexture();
       ~LTexture();
       bool loadFromFile( SDL_Renderer* renderer, std::string path );
       void free();
       void setColor( Uint8 red , Uint8 green, Uint8 blue );
       void setBlendMode( SDL_BlendMode blending );
       void setAlpha( Uint8 alpha );
       void render(SDL_Renderer* renderer, SDL_Rect *source, int x, int y, int w, int h, bool dir);
       int getWidth();
       int getHeight();
     private:
       SDL_Texture* mTexture;
       int mWidth;
       int mHeight;
};
LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile( SDL_Renderer* renderer, std::string path )
{
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
    {
        std::cout << "Load image Error: "<<IMG_GetError()<<'\n';
    } 
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if ( newTexture == NULL )
        {
            std::cout << "Create texture error: " << SDL_GetError() << std::endl;
        } 
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    if ( mTexture != NULL)
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::render(SDL_Renderer* renderer, SDL_Rect *source, int x = 0, int y = 0, int w =- 1, int h =- 1, bool dir=1)
{
    SDL_Rect dest = { x, y, w, h };
    if(w == -1)
        dest.w = mWidth,
        dest.h = mHeight;
    int errorCode = SDL_RenderCopyEx(renderer, mTexture, source, &dest, 0, NULL, dir?SDL_FLIP_NONE:SDL_FLIP_HORIZONTAL);
    if (errorCode != 0)
        std::cout << "Render copy error: " << SDL_GetError() << std::endl;
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}
