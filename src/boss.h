#pragma once 
#include "constants.h"
#include "gameTexture.h"
#include "collision.h"
#include "bullet.h"
using namespace std;

struct boss
{
    int x, y, hp, phase;
    //0: norm, 1: 50% hp, 2: 25% hp

    int phaseUpdated = 0;
    int velX = 5,velY = 5;
    int prevShootTime = 0;
    const int entityID = 1;
    const int width = 300;
    const int height = 240;

    boss(int x, int y, int hp);
    void spawn(int x, int y, int hp);

    void move();
    void shoot();
    void syncData();
    void render(SDL_Renderer* renderer);
};

boss::boss(int x = 640, int y = 200, int hp = bossMaxHP)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    velX = velY = 5;
    phase = phaseUpdated = 0;
}

void boss::spawn(int x = bossSpawnX, int y = bossSpawnY, int hp = bossMaxHP)
{
    this->x = x;
    this->y = y;
    this->hp = hp;
    velX = velY = 5;
    phase = phaseUpdated = 0;
}

pair<int,int> firePoint[12] = {{15,15},{150,0},{290,15},{30,240},{270,240},
                              {150,240},{95,225},{205,225},{115,230},{185,230},
                              {290,160},{15,160}};


void boss::move()
{
    phase = 0;
    if (hp <= bossMaxHP / 2) phase = 1;
    if (hp <= bossMaxHP / 4) phase = 2;
    
    // launching projectile after every 2.5 seconds 
    double timeDiff = 2.5 - phase;
    if (SDL_GetTicks() - prevShootTime >= timeDiff * 1000 && y <= SCREEN_HEIGHT / 3)
    {
        prevShootTime = SDL_GetTicks();
        shoot();
    }

    if (phase == 1 && phaseUpdated == 0) {
        velX *= 1.5;
        velY *= 1.5;
        phaseUpdated = 1;
    }

    if (phase == 2 && phaseUpdated == 1) {
        velX *= 1.7;
        velY *= 1.7;
        phaseUpdated = 2;
    }

    x += velX;
    y += velY;

    if (x < 40 || x + width > SCREEN_WIDTH - 40) velX =- velX;
    if (y < 40 || y + height > SCREEN_HEIGHT - 40) velY =- velY;

    x = std::min(SCREEN_WIDTH - 40, std::max(40, x));
    y = std::min(SCREEN_HEIGHT - 40, std::max(40, y));
}

void boss::shoot()
{
    // boss center: 
    int cx = x + width / 2;
    int cy = y + height / 2;

    int px;
    int py;

    for (int i = 0; i < 12; i++)
    {
        px = x + firePoint[i].first;
        py = y + firePoint[i].second;
        double vx, vy;

        calculateBulletVelocity(cx, cy, px, py, vx, vy, 5);
        addBullet(px, py, vx, vy, 0);
    }
}

void boss::syncData()
{
    if (entityList[entityID].wasHit)
    {
        hp -= 2;
        entityList[entityID].wasHit = 0;
    }

    entityList[entityID].hitbox.x = x;
    entityList[entityID].hitbox.y = y;
    entityList[entityID].hitbox.w = width;
    entityList[entityID].hitbox.h = height;
}   

//SDL_Rect bossRect[10] = {};
SDL_Rect bossRect = { 0,0,112,78 };

void boss::render(SDL_Renderer* renderer)
{
    if (hp <= 0) return;
    bossTex.render(renderer, &bossRect, x, y, 112 * 2.678, 78 * 3.076);
    // &bossRect[SDL_GetTicks()/1000 % 10]
}