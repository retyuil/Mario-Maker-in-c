#include <stdbool.h>
#include "init.h"
typedef struct {
    int run_frame;
    int direction_faced;
    bool alive;
    bool jump_pressed;
    bool can_jump;
    bool left_pressed;
    bool right_pressed;
    bool sprint;
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    int size;
} Player;

Player create_player(){
    Player player;
    player.run_frame = 0;
    player.direction_faced = 0;
    player.alive = true;
    player.jump_pressed = false;
    player.can_jump = true;
    player.left_pressed = false;
    player.right_pressed = false;
    player.sprint = false;
    player.x_pos = 0;
    player.y_pos = 64;
    player.x_vel = 0;
    player.y_vel = 0;
    player.size = SIZE;
    return player;
}
