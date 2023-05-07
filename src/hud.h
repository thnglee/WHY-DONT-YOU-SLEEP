#pragma once
#include "constants.h"
#include "SDL.h"
#include "gameTexture.h"
#include "text.h"

void drawHud(SDL_Renderer* renderer, int playerHP, int bossHP);
void drawPlayerHealth(SDL_Renderer* renderer,int HP);
void drawBossHealth(SDL_Renderer* renderer,int HP);

void drawHud(SDL_Renderer* renderer, int playerHP, int bossHP)
{
    drawPlayerHealth(renderer, playerHP);
    if (bossHP > 0) drawBossHealth(renderer, bossHP);
}

void drawPlayerHealth(SDL_Renderer* renderer, int HP)
{
    int xoff = 50;
    int yoff = 50;

    for(int i = 0; i < HP; i++)
    {
        playerHealth.render(renderer, NULL, xoff, yoff, 25, 25);
        xoff += 30;
    }
}

void drawBossHealth(SDL_Renderer* renderer,int HP)
{
    drawText(renderer,1160,130,30,to_string(HP));
    //1160 160 1160 640

    SDL_SetRenderDrawColor(renderer,242,211,171,255);
    SDL_RenderDrawRect(renderer,new SDL_Rect({1160,160,40,480}));

    SDL_SetRenderDrawColor(renderer,242,211,171,255);
    int yy = std::min(639,161+int((1-1.0 * HP/ bossMaxHP)*(639 - 161)));

    SDL_RenderFillRect(renderer,new SDL_Rect({1161, yy, 38,639 - yy}));
}