#ifndef PLATFORMER_H
#define PLATFORMER_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "const.h"



typedef struct {
    SDL_Renderer* rend;
    SDL_Window* wind;
    SDL_Texture* bg_texture;
    SDL_Texture* ground_texture;
    SDL_Texture* mario_sprites[NB_SPRITES_MARIO];
    SDL_Texture* decor_sprites[NB_SPRITES_DECOR];
    SDL_Texture* enemy_sprites[NB_SPRITES_ENEMY];
} Motor;



bool check_collision(SDL_Rect a, SDL_Rect b, float camera_x);

int init();


Motor create_motor();

#endif
