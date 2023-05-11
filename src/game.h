#pragma once
#include "constants.h"
#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "terrain.h"
#include "SDLcore.h"
#include "gameTexture.h"
#include "player.h"
#include "boss.h"
#include "menu.h"
#include "hud.h"
#include "text.h"
#include "sound.h"
using namespace std;


class Game
{
public:
    Game();
    ~Game();
    void initGameEntity();
    void introMenu();
    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();
    void fixMenuChoice(int l, int r);

    void handleEvent(SDL_Event &e);
    void handleEventMenu(SDL_Event &e);
    void handleEventInGame(SDL_Event &e);
    void update();
    void render();

    void run();

private:
    bool quit;
    bool isStartMenu;
    bool inGame;
    bool paused;
    bool isGameOver;

    int menuChoice;
    int choice;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    player P;
    boss B;
};

Game::Game()
{
    if (!initSDL(window, renderer))
    {
        std::cout << "SDL Init Error" << std::endl;
        return ;
    }
    loadAllTexture(renderer);
    loadSounds();
    loadMap();
    initMenuChoice();
    quit = false;
}

Game::~Game()
{
    quitSDL(window, renderer);
}

void Game::initGameEntity()
{
    P.spawn();
    B.spawn();
    for(int i = 0; i < maxBulletNumber; i++) 
        bulletList[i].active = 0;
}

void Game::introMenu()
{
    isStartMenu = true;
    inGame = false;
    isGameOver = false;
    paused = false;
    quit = false;
    menuChoice = 1;
    choice = 0;
}

void Game::startGame()
{
    isStartMenu = false;
    inGame = true;
    isGameOver = false;
    paused = false;
    quit = false;
    menuChoice = 1;
    choice = 0;
    initGameEntity();
}

void Game::pauseGame()
{
    paused = true;
    menuChoice = 1;
    choice = 0;
}

void Game::resumeGame()
{
    paused = false;
}

void Game::endGame()
{
    isStartMenu = false;
    inGame = false;
    isGameOver = true;
    paused = false;
    quit = false;
    menuChoice = 1;
    choice = 0;
}

void Game::fixMenuChoice(int l,int r)
{
    if(menuChoice < l) menuChoice = r;
    if(menuChoice > r) menuChoice = l;
    if(menuChoice == 7) quit = true;

}

void Game::handleEventMenu(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_w: case SDLK_UP:
                menuChoice--;
                break;

            case SDLK_s: case SDLK_DOWN:
                menuChoice++;
                break;

            case SDLK_RETURN:
                choice = menuChoice;
                break;
        }
    }
}

void Game::handleEventInGame(SDL_Event &e)
{
    P.handleEvent(e);
}

void Game::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_QUIT)
    {
        quit = true;
        return ;
    }
   /* if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if(e.key.keysym.sym == SDLK_KP_PLUS) volume += 10;
        else if(e.key.keysym.sym == SDLK_KP_MINUS) volume-=10;
        adjustVolume();
    }*/
    if (isStartMenu || isGameOver) handleEventMenu(e);
    if (inGame)
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE && e.key.repeat ==0)
        {
            if (paused) resumeGame();
            else pauseGame();
            return ;
        }
        if (paused) handleEventMenu(e);
        else handleEventInGame(e);
    }
}

void Game::update()
{
    launchingBullets();
    P.move();
    P.syncData();
    B.move();
    B.syncData();
}

void Game::run()
{
    introMenu();
    render();
    while(!quit)
    {
        replayBgMusic();
        while(!quit && isStartMenu)
        {
            while(SDL_PollEvent(&e))
            {
                handleEvent(e);
                fixMenuChoice(1,2);
            }

            if(choice != 0) playSFX(menuSFX);
            if(choice==1) startGame();
            if(choice==2) quit = true;
            render();
        }

        if(quit) break ;
        while(!quit && inGame)
        {
            while(SDL_PollEvent(&e))
            {
                handleEvent(e);
                fixMenuChoice(1, 4);
            }

            if(paused)
            {
                if(choice != 0) playSFX(menuSFX);
                if(choice == 1) resumeGame();
                if(choice == 2) toggleBgMusic();
                if(choice == 3) ;
                if(choice == 4) quit = 1;
                choice = 0;
            }
            else update();

            render();
            if(P.hp == 0 || B.hp == 0) endGame();
        }

        if(quit) break;

        while(isGameOver && !quit)
        {
            while(SDL_PollEvent(&e))
            {
                handleEvent(e);
                fixMenuChoice(1,3);
            }

            if(choice != 0) playSFX(menuSFX);
            if(choice == 1) startGame(); // play again
            if(choice == 2) introMenu(); //go back to menu  
            if(choice == 3) quit = true; //quit
            render();
        }
    }

}

void Game::render()
{
    int startTime = SDL_GetTicks(); 

    SDL_SetRenderDrawColor(renderer, 39, 39, 68, 255);
    SDL_RenderClear(renderer);

    if(isStartMenu) drawMenuStart(renderer,menuChoice);

    if(inGame)
    {
        renderTerrain(renderer);
        renderBullets(renderer);
        P.render(renderer);
        B.render(renderer);

        if(paused) drawMenuPause(renderer,menuChoice);
        else drawHud(renderer, P.hp, B.hp);    
    }

    if(isGameOver)
    {
        if(P.hp == 0) drawMenuOver(renderer,0,menuChoice);
        else drawMenuOver(renderer,1,menuChoice);
    }
    SDL_RenderPresent(renderer);

    // framerate manipulation: 
    int frameTime = std::max(int(SDL_GetTicks() - startTime),1);
    if(frameTime < 1000 / FPS) SDL_Delay(1000 / FPS - frameTime);
}
