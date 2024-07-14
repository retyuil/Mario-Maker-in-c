#include "player.h"

int process_physics(Player* player, float *camera_x, SDL_Rect *bg_elements, int nb_blocks, SDL_Rect *ground_elements, int nb_sol);
bool check_collision_down(SDL_Rect a, SDL_Rect b);
bool check_collision_up(SDL_Rect a, SDL_Rect b);
bool check_collision_left(SDL_Rect a, SDL_Rect b);
bool check_collision_right(SDL_Rect a, SDL_Rect b);