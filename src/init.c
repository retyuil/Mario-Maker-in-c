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




int init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}



SDL_Window* create_window() {
    SDL_Window* wind = SDL_CreateWindow("Mario",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        WIDTH, HEIGHT, 0);
    if (!wind) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }
    return wind;
}

SDL_Renderer* create_renderer(SDL_Window* wind) {
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(wind, -1, render_flags);
    if (!rend) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    return rend;
}

SDL_Texture* create_background(SDL_Renderer* rend, SDL_Window* wind) {
    SDL_Surface* bg_surface = SDL_LoadBMP("background.bmp");
    if (!bg_surface) {
        printf("Error loading background image: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    SDL_Texture* bg_texture = SDL_CreateTextureFromSurface(rend, bg_surface);
    SDL_FreeSurface(bg_surface);
    if (!bg_texture) {
        printf("Error creating texture from surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    return bg_texture;
}

SDL_Texture* create_texture_mario(SDL_Renderer* rend, SDL_Window* wind, SDL_Texture* bg_texture) {
    SDL_Surface* sprite_surface = SDL_LoadBMP("mario.bmp");
    if (!sprite_surface) {
        printf("Error loading sprite image: %s\n", SDL_GetError());
        SDL_DestroyTexture(bg_texture);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    SDL_Texture* sprite_texture = SDL_CreateTextureFromSurface(rend, sprite_surface);
    SDL_FreeSurface(sprite_surface);
    if (!sprite_texture) {
        printf("Error creating sprite texture from surface: %s\n", SDL_GetError());
        SDL_DestroyTexture(bg_texture);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    return sprite_texture;
}


SDL_Texture* create_texture_mario_run(SDL_Renderer* rend, SDL_Window* wind, SDL_Texture* bg_texture) {
    SDL_Surface* sprite_surface = SDL_LoadBMP("mario_run.bmp");
    if (!sprite_surface) {
        printf("Error loading sprite image: %s\n", SDL_GetError());
        SDL_DestroyTexture(bg_texture);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    SDL_Texture* sprite_texture = SDL_CreateTextureFromSurface(rend, sprite_surface);
    SDL_FreeSurface(sprite_surface);
    if (!sprite_texture) {
        printf("Error creating sprite texture from surface: %s\n", SDL_GetError());
        SDL_DestroyTexture(bg_texture);
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(wind);
        SDL_Quit();
        return NULL;
    }
    return sprite_texture;
}

SDL_Texture* create_texture_mario_run2(SDL_Renderer* rend, SDL_Window* wind, SDL_Texture* bg_texture) {
    SDL_Surface* sprite_surface = SDL_LoadBMP("mario_run2.bmp");
    SDL_Texture* sprite_texture = SDL_CreateTextureFromSurface(rend, sprite_surface);
    SDL_FreeSurface(sprite_surface);
    return sprite_texture;
}


SDL_Texture* create_texture_from_file(SDL_Renderer* rend, SDL_Window* wind, const char* file_path) {
    SDL_Surface* sprite_surface = SDL_LoadBMP(file_path);
    SDL_Texture* sprite_texture = SDL_CreateTextureFromSurface(rend, sprite_surface);
    SDL_FreeSurface(sprite_surface);
    return sprite_texture;
}



Motor create_motor() {
    Motor motor;

    motor.wind = create_window();

    motor.rend = create_renderer(motor.wind);

    motor.ground_texture = create_texture_from_file(motor.rend, motor.wind,"sprites/ground.bmp");
    motor.bg_texture = create_texture_from_file(motor.rend, motor.wind,"sprites/background.bmp");

    motor.mario_sprites[0] = create_texture_from_file(motor.rend, motor.wind,"sprites/mario.bmp");
    motor.mario_sprites[1] = create_texture_from_file(motor.rend, motor.wind,"sprites/mario_run.bmp");
    motor.mario_sprites[2] = create_texture_from_file(motor.rend, motor.wind,"sprites/mario_run2.bmp");
    motor.mario_sprites[3] = create_texture_from_file(motor.rend, motor.wind,"sprites/mario_b.bmp");
    motor.mario_sprites[4] = create_texture_from_file(motor.rend, motor.wind,"sprites/mario_b_run.bmp");
    motor.mario_sprites[5] = create_texture_from_file(motor.rend, motor.wind,"sprites/mario_b_run2.bmp");

    motor.decor_sprites[0] = create_texture_from_file(motor.rend, motor.wind,"sprites/block.bmp");

    motor.enemy_sprites[0] = create_texture_from_file(motor.rend, motor.wind,"sprites/gumba1.bmp");
    motor.enemy_sprites[1] = create_texture_from_file(motor.rend, motor.wind,"sprites/gumba2.bmp");
    motor.enemy_sprites[2] = create_texture_from_file(motor.rend, motor.wind,"sprites/gumba3.bmp");

    return motor;
}