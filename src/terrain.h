#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "constants.h"
#include "texture.h"
#include "gameTexture.h"


int mapT[nRow][nCol];
void loadMap()
{
    std::ifstream map("assets/map.csv");
    std::string line,dat;
    int i = 0, j = 0;

    while(getline(map,line))
    {
        std::stringstream s(line);
        while(getline(s,dat,','))
        {
            mapT[i][j] = atoi(dat.c_str());
            j++;
        }
        i++;
        j = 0;
    }
}

SDL_Rect tType[2] = {{0,0,tSize,tSize},{tSize,0,tSize,tSize}};
void renderTerrain(SDL_Renderer* renderer)
{
    for(int i = 0; i < nRow; i++)
    {
        for(int j = 0; j < nCol; j++)
        {   
            tile.render(renderer,&tType[mapT[i][j]],j*tSize,i*tSize,tSize,tSize);
        }   
    }
}

