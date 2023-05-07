#define NOMINMAX
#include <iostream>
#include <windows.h>
#include "Game.h"

int main(int argc, char* args[])
{
    //FreeConsole();
    std::cout << "Game generated" << std::endl;
    Game Game;
    Game.run();
    return 0;
}