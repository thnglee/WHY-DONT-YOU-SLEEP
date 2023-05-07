#pragma once
#include "SDL_mixer.h"
#include "constants.h"

Mix_Music *bgMusic;
Mix_Chunk *pShoot, *pHit, *bHit, *bShoot, *menuSFX;

void loadSounds() {
    bgMusic = Mix_LoadMUS("assets/mouse_eating.mp3");
    menuSFX = Mix_LoadWAV("assets/menuSFX.wav");
    // pShoot = Mix_LoadWAV("assets/pShoot.wav");
    // pHit = Mix_LoadWAV("assets/pHit.wav");
    // bHit = Mix_LoadWAV("assets/bHit.wav");
    // bShoot = Mix_LoadWAV("assets/bShoot.wav");
}
void toggleBgMusic() {
    if(Mix_PlayingMusic() == 0) Mix_PlayMusic(bgMusic, -1);
    else {
        if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
        else Mix_PauseMusic();
    }
}

void replayBgMusic() {
    if(Mix_PlayingMusic() == 1) Mix_HaltMusic();
    Mix_PlayMusic(bgMusic, -1);
    Mix_VolumeMusic(volume);
}

void playSFX(Mix_Chunk *sfx) {
    Mix_VolumeChunk(menuSFX,volume);
    Mix_PlayChannel(-1, sfx, 0);
}

void adjustVolume() {
    volume = std::min(max(0,volume),128);
    Mix_VolumeMusic(volume);
    Mix_VolumeChunk(menuSFX,volume);
}