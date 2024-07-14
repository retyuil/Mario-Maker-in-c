#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "init.h"
#include "player.h"



bool check_collision_down(SDL_Rect a, SDL_Rect b)
{
    return (a.y + a.h < b.y + b.h*0.5
        && a.y + a.h > b.y 
        && a.x + a.w  > b.x + 8
        && a.x < b.x + b.w - 8);
}

bool check_collision_up(SDL_Rect a, SDL_Rect b)
{
    return (a.y > b.y + 0.5*b.h
        && a.y  < b.y + b.h
        && a.x + a.w > b.x + 8
        && a.x < b.x + b.w - 8);
}

bool check_collision_left(SDL_Rect a, SDL_Rect b)
{
    return (a.y < b.y + b.h 
        && a.y + a.h > b.y 
        && a.x  < b.x + b.w - 4//debut de la detection au debut du block
        && a.x   > b.x + b.w*0.5 //arret de la dectetion à la moitié du block
        );
}

bool check_collision_right(SDL_Rect a, SDL_Rect b)
{
    return (a.y < b.y + b.h 
        && a.y + a.h > b.y 
        && a.x  + a.w > b.x + 4 //debut de la detection au debut du block
        && a.x  + a.w < b.x + b.w*0.5 //arret de la dectetion à la moitié du block
        );
}




int process_physics(Player* player, float *camera_x, SDL_Rect *bg_elements, int nb_blocks, SDL_Rect *ground_elements, int nb_sol){
    player->x_vel = (player->right_pressed - player->left_pressed) * SPEED + (player->right_pressed - player->left_pressed) * SPEED * player->sprint * 0.5;
    player->y_vel += GRAVITY;
    if (player->jump_pressed && player->can_jump)
    {
        player->y_vel = JUMP;
    }
    player->x_pos += player->x_vel / 60;
    player->y_pos += player->y_vel / 60;
    if (player->x_pos <= 0)
        player->x_pos = 0;
    if (player->y_pos <= 0)
        player->y_pos = 0;
    *camera_x = player->x_pos - WIDTH / 2 + SIZE / 2;
    if (*camera_x < 0) *camera_x = 0;
    SDL_Rect player_rect = { (int)player->x_pos, (int)player->y_pos, SIZE, SIZE };

    SDL_Rect player_hitbox = { (int)player->x_pos, (int)player->y_pos, SIZE, SIZE };

    player_hitbox.x = (int)(player->x_pos);
    player_hitbox.y = (int)player->y_pos;

    player->can_jump = false;
        for (int i = 0; i < nb_blocks; ++i)
        {
                if (check_collision_down(player_hitbox, bg_elements[i]))
                {

                    if (player->y_vel > 0) // Moving down
                    {
                        player->y_pos = bg_elements[i].y - player_rect.h;
                        player->y_vel = 0;
                        player->can_jump = true;
                    }
                }

                if (check_collision_up(player_hitbox, bg_elements[i]))
                {
                    if (player->y_vel < 0) // Moving up
                    {
                        player->y_pos = bg_elements[i].y + bg_elements[i].h;
                        player->y_vel = 0;
                    }
                }

                if (check_collision_right(player_hitbox, bg_elements[i]))
                {
                    if (player->x_vel > 0) // Moving right
                    {
                        player->x_pos -= (player->x_vel) / 60;
                        player->x_vel = 0;
                    }
                }

                if (check_collision_left(player_hitbox, bg_elements[i]))
                {
                    
                    if (player->x_vel < 0) // Moving left
                    {
                        player->x_pos -= (player->x_vel) / 60;
                        player->x_vel = 0;
                    }
                }

        }


        for (int i = 0; i < nb_sol; ++i){
                if (check_collision_down(player_hitbox, ground_elements[i]))
                {
                    if (player->y_vel > 0) // Moving down
                    {
                        player->y_pos = ground_elements[i].y - player_rect.h;
                        player->y_vel = 0;
                        player->can_jump = true;
                    }
                }
        }

        player_rect.x = (int)(player->x_pos - *camera_x);
        player_rect.y = (int)player->y_pos;
        player_hitbox.x = player_rect.x;
        player_hitbox.y = player_rect.y;

    if (player->y_pos > HEIGHT){
        player->alive = false;
    }
}