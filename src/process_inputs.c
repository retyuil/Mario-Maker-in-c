#include "player.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

int process_input(Player* player){
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

            switch (event.type)
            {
            case SDL_QUIT:
                player->alive = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    player->jump_pressed = true;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    player->left_pressed = true;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    player->right_pressed = true;
                    break;
                case SDL_SCANCODE_LSHIFT:
                    player->sprint = true;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    player->jump_pressed = false;
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    player->left_pressed = false;
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    player->right_pressed = false;
                    break;
                case SDL_SCANCODE_LSHIFT:
                    player->sprint = false;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
}