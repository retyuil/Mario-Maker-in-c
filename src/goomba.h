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


Goomba create_goomba(float x_pos, float y_pos, float upper_limit, float down_limit);
int process_goomba(Goomba* goomba);
int check_collision_goomba(Goomba* goomba, Player* player);