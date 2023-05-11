#pragma once
#include "constants.h"
#include"SDL.h"
#include <vector>
#include "text.h"

vector<SDL_Rect> choiceBox[3];
vector<string> choiceContent[3];
string fontHeader = "assets/pixeboy.ttf";
string fontContent = "assets/pixeboy.ttf";

void initMenuChoice()
{
    //start menu
    choiceBox[0].push_back({550,335,180,50});
    choiceBox[0].push_back({550,335+50+85,180,50});
    choiceContent[0].push_back("Start");
    choiceContent[0].push_back("Quit");

    // pause game screen:
    choiceBox[1].push_back({550,240,180,50});
    choiceBox[1].push_back({550,240+50+65,180,50});
    choiceBox[1].push_back({550,240+2*50+2*65,180,50});
    choiceBox[1].push_back({550,240+3*50+3*65,180,50});
    choiceContent[1].push_back("Resume");
    choiceContent[1].push_back("Music");
    choiceContent[1].push_back("Sound");
    choiceContent[1].push_back("Quit");
    
    //game over menu: 
    choiceBox[2].push_back({550,300,180,50});
    choiceBox[2].push_back({550,300+50+85,180,50});
    choiceBox[2].push_back({550,300+2*50+2*85,180,50});
    choiceContent[2].push_back("Again");
    choiceContent[2].push_back("Menu");
    choiceContent[2].push_back("Quit");
}

void drawMenu(SDL_Renderer* renderer, vector<SDL_Rect> choiceBoxes, vector<string> choiceContent, int choice)
{
    //drawText(renderer, 5, 5, 30, to_string(choice));
    int choiceNumber = choiceBoxes.size();
    for(int i = 0; i < choiceNumber; i++)
    {
        if(i == choice - 1)
        {
            drawTextCenter(renderer,choiceBoxes[i].x,choiceBoxes[i].y,40,choiceContent[i],choiceBoxes[i].w,choiceBoxes[i].h,{ 242,211,171,255},fontContent);
        }
        else
            drawTextCenter(renderer,choiceBoxes[i].x,choiceBoxes[i].y,40,choiceContent[i],choiceBoxes[i].w,choiceBoxes[i].h,{255,255,255,255},fontContent);
    }
}

void drawMenuStart(SDL_Renderer* renderer,int menuChoice)
{
    SDL_SetRenderDrawColor(renderer, 39, 39, 68, 255);
    SDL_RenderClear(renderer);
    drawText(renderer,380,150,67,"why don't you sleep ?");
    drawMenu(renderer,choiceBox[0],choiceContent[0],menuChoice);
}

void drawMenuPause(SDL_Renderer* renderer,int menuChoice)
{
    SDL_Texture* faded;
    faded = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL_SetTextureBlendMode(faded,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(faded,200);
    SDL_SetRenderTarget(renderer,faded);
    SDL_SetRenderDrawColor(renderer, 39, 39, 68,255);
    SDL_RenderClear(renderer);
    drawText(renderer,470,95,67,"take a break");
    drawMenu(renderer,choiceBox[1],choiceContent[1],menuChoice);
    SDL_SetRenderTarget(renderer,NULL);
    SDL_RenderCopy(renderer,faded,NULL,NULL);
    SDL_DestroyTexture(faded);
}

void drawMenuOver(SDL_Renderer* renderer,bool win,int menuChoice)
{
    SDL_SetRenderDrawColor(renderer, 39, 39, 68,255);
    SDL_RenderClear(renderer);
    if(win) drawText(renderer,490,150,67,"you did it !",{ 251,245,239, 255});
    else drawText(renderer,510,150,67,"Game Over",{ 251,245,239, 255});

    drawMenu(renderer,choiceBox[2],choiceContent[2],menuChoice);
}
