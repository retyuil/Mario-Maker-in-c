#include <stdbool.h>
#include "init.h"
#include "physics.h"
#define GOOMBA_SPEED 3

typedef struct {
    int direction_faced;
    bool alive;
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    float upper_limit;
    float down_limit;
    int size;
    int sprite;
    int frame_counter;
    int frame_counter_death;
} Goomba;


Goomba create_goomba(float x_pos, float y_pos, float upper_limit, float down_limit){
    Goomba goomba;
    goomba.direction_faced = 0;
    goomba.alive = true;
    goomba.x_pos = x_pos;
    goomba.y_pos = y_pos;
    goomba.x_vel = GOOMBA_SPEED;
    goomba.y_vel = 0;
    goomba.upper_limit = upper_limit;
    goomba.down_limit = down_limit;
    goomba.size = SIZE;
    goomba.sprite = 0;
    goomba.frame_counter = 0;
    goomba.frame_counter_death = 0;
    return goomba;
}


int process_goomba(Goomba* goomba){
    if (goomba->alive){
    if (goomba->x_pos > goomba->upper_limit){
        goomba->x_vel = -GOOMBA_SPEED;
    }
    if (goomba->x_pos < goomba->down_limit){
        goomba->x_vel = GOOMBA_SPEED;
    }
    goomba->x_pos = goomba->x_pos + goomba->x_vel;
    goomba->frame_counter++;
    if (goomba->frame_counter >= 10) {
        goomba->sprite = (goomba->sprite + 1) % 2;
        goomba->frame_counter = 0; // Réinitialise le compteur après avoir changé de sprite
    }
    }
    else{
        if (goomba->frame_counter_death < 40){
            goomba->frame_counter_death += 1;
        }
    }
}



int check_collision_goomba(Goomba* goomba, Player* player){
    if (goomba->alive){
    SDL_Rect player_hitbox = { (int)player->x_pos, (int)player->y_pos, SIZE, SIZE };
    SDL_Rect goomba_hitbox = { (int)goomba->x_pos, (int)goomba->y_pos, SIZE, SIZE };

                if (check_collision_down(player_hitbox, goomba_hitbox))
                {

                    if (player->y_vel > 0) // Moving down
                    {
                        player->y_pos = goomba_hitbox.y - player_hitbox.h;
                        player->y_vel = 0;
                        player->y_vel += JUMP*0.8;
                        goomba->alive = false;
                        goomba->sprite = 2;
                    }
                }

                if (check_collision_right(goomba_hitbox,player_hitbox))
                {
                        player->x_pos -= (player->x_vel) / 60;
                        player->x_vel = 0;
                        player->alive = false;
                }

                if (check_collision_left(goomba_hitbox,player_hitbox))
                {
                        player->x_pos -= (player->x_vel) / 60;
                        player->x_vel = 0;
                        player->alive = false;
                }
    }
}
