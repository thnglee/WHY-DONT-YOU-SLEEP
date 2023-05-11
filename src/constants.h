#pragma once

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;
const double PI = 3.14159265358979323846;

int volume = 48;

// tile:
const int tSize = 40;
const int nRow = SCREEN_HEIGHT / tSize;
const int nCol = SCREEN_WIDTH / tSize;

// player:
const int pVel = 9;
const int pSize = 15;
const int maxHP = 3;
const int playerSpawnX = SCREEN_WIDTH / 2;
const int playerSpawnY = SCREEN_HEIGHT - 40 - pSize;

// boss:
const int bossMaxHP = 1000;
const int bossSpawnX = SCREEN_WIDTH / 2;
const int bossSpawnY = 40;

// bullet:
const int bSize = 3;
const int maxBulletNumber = 700;
const int bulletVel = 11;

