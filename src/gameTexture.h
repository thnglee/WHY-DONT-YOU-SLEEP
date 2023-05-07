#pragma once
#include "texture.h"
#include "constants.h"

// tex init:
LTexture bossTex;
LTexture bossBulletTex;
LTexture tile;
LTexture playerHealth;

void loadAllTexture(SDL_Renderer* renderer)
{
    // boss texture and boss projectiles:
    bossTex.loadFromFile(renderer, "./assets/Ocho.png");
    bossBulletTex.loadFromFile(renderer, "./assets/projectile.png");

    // terrain texture:
    tile.loadFromFile(renderer, "./assets/tile.png");

    // hud implements:
    playerHealth.loadFromFile(renderer, "./assets/pink.png");
}

