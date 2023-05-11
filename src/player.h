#pragma once
#include "constants.h"
#include "SDL.h"
#include "texture.h"
#include "terrain.h"
#include "bullet.h"
#include "collision.h"

struct player
{
    int x, y, hp;
    int velX, velY;
    bool shoot;
    int hitTime;
    bool invincible = 0;

    const int entityID = 0; // entity id
    const int width = pSize;
    const int height = pSize;

    SDL_Color normal_state = { 242, 211, 242, 255 };
    SDL_Color invincible_state = {0,0,0, 255};

    player(int x, int y, int hp);
    void spawn(int x, int y, int hp);
    //~player();

    void handleEvent(SDL_Event &e);
    void move();
    void render(SDL_Renderer* renderer);
    void syncData();
    bool struck();
};

player::player(int x = 0, int y = 0, int hp = maxHP)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    velX = velY = 0;
    shoot = 0;
    invincible = 0;
    hitTime = 0;
}

void player::spawn(int x = playerSpawnX, int y = playerSpawnY, int hp = maxHP)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    velX = velY = 0;
    shoot = 0;
    invincible = 0;
    hitTime = 0;
}

void player::handleEvent(SDL_Event &e) 
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT: case SDLK_d:
                velX += pVel;
                break;

            case SDLK_LEFT: case SDLK_a: 
                velX -= pVel;
                break;

            case SDLK_DOWN: case SDLK_s:
                velY += pVel;
                break;

            case SDLK_UP: case SDLK_w:
                velY -= pVel;
                break;
        }
    } 

    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_d:
                velX -= pVel;
                break;

            case SDLK_a: 
                velX += pVel;
                break;

            case SDLK_w: 
                velY += pVel;
                break;

            case SDLK_s: 
                velY -= pVel;
                break;
        }
    }

    if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0) shoot = 1;
    if(e.type == SDL_MOUSEBUTTONUP && e.key.repeat == 0) shoot = 0;
}

void player::move()
{
    bool hit = 0; //dont care
    bool hitEnemy = 0;
    nextPos(x, y, velX, velY, pSize, hit, hitEnemy);

    if (hitEnemy) hp--;

    if (shoot)
    {
        int px, py;
        double vx, vy;

        SDL_GetMouseState(&px, &py);
        calculateBulletVelocity(x, y, px, py, vx, vy);
        addBullet(x, y, vx, vy);
    }
}

void player::syncData()
{
    if (invincible && SDL_GetTicks() - hitTime >= 2000) {
        invincible = 0;
    }
    if (invincible == 0 && (entityList[entityID].wasHit || struck()))
    {
        hp--;
        invincible = 1;
        hitTime = SDL_GetTicks();
        entityList[entityID].wasHit = 0;
    }
    entityList[entityID].hitbox.x = x;
    entityList[entityID].hitbox.y = y;
    entityList[entityID].hitbox.w = width;
    entityList[entityID].hitbox.h = height;
}

void player::render(SDL_Renderer* renderer)
{   
    if (!invincible) SDL_SetRenderDrawColor(renderer, normal_state.r, normal_state.g, normal_state.b, normal_state.a);
    else SDL_SetRenderDrawColor(renderer, invincible_state.r, invincible_state.g, invincible_state.b, invincible_state.a);
    SDL_RenderFillRect(renderer,new SDL_Rect({ x, y, pSize, pSize}));
}

bool player::struck()
{
    return checkHitEntity(0, 1);
}