#include <stdbool.h>

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

Player create_player();