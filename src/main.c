#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "init.h"
#include "physics.h"
#include "goomba.h"
#include "process_inputs.h"


int count_lines_in_file(FILE *file) {
    int count = 0;
    char ch;

    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file); // Remet le pointeur de fichier au début
    return count;
}


int main(int argc, char* argv[])
{
    //-----------------CREATION DU MOTEUR---------------------------
    Motor motor = create_motor();
    SDL_Renderer* rend = motor.rend;
    SDL_Window* wind = motor.wind;

    //-----------------LOAD SPRITES---------------------------------
    SDL_Texture* bg_texture = motor.bg_texture;
    SDL_Texture* ground_texture = motor.ground_texture;
    SDL_Texture* mario_sprites[NB_SPRITES_MARIO];
    SDL_Texture* decor_sprites[NB_SPRITES_DECOR];
    SDL_Texture* enemy_sprites[NB_SPRITES_ENEMY];
    memcpy(mario_sprites, motor.mario_sprites, sizeof(mario_sprites));
    memcpy(decor_sprites, motor.decor_sprites, sizeof(decor_sprites));
    memcpy(enemy_sprites, motor.enemy_sprites, sizeof(enemy_sprites));


    Player player = create_player();

    
    SDL_Rect player_rect = { (int)player.x_pos, (int)player.y_pos, SIZE, SIZE };

    SDL_Rect player_hitbox = { (int)player.x_pos, (int)player.y_pos, SIZE, SIZE };

    float camera_x = 0;




    //----------------------------LOAD GOOMBA FROM TXT----------------------------
    FILE *file = fopen("map/goombas.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    int nb_goombas = count_lines_in_file(file);
    Goomba *goombas = (Goomba *)malloc(nb_goombas * sizeof(Goomba));
    if (goombas == NULL){
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < nb_goombas; i++){
        int x, y, x_max, x_min;
        if (fscanf(file, "%d,%d,%d,%d\n", &x, &y, &x_max, &x_min) != 4) {
            fprintf(stderr, "Error reading file\n");
            free(goombas); // Libération de la mémoire en cas d'erreur
            fclose(file);
            return EXIT_FAILURE;
        }
        goombas[i] = create_goomba(x, y, x_max, x_min);
    }

    SDL_Rect goomba_rects[nb_goombas];
    for (int i = 0; i < nb_goombas; i++){
        goomba_rects[i].w = SIZE;
        goomba_rects[i].h = SIZE;
    }
    //---------------------------LOAD BLOCKS FROM TXT------------------------------

    FILE *file1 = fopen("map/blocks.txt", "r");
    if (file1 == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Compter le nombre de lignes dans le fichier
    int nb_blocks = count_lines_in_file(file1);

    // Allocation dynamique de la mémoire pour bg_elements
    SDL_Rect *bg_elements = (SDL_Rect *)malloc(nb_blocks * sizeof(SDL_Rect));
    if (bg_elements == NULL) {
        perror("Failed to allocate memory");
        fclose(file1);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < nb_blocks; i++) {
        if (fscanf(file1, "%d,%d,%d,%d\n", &bg_elements[i].x, &bg_elements[i].y, &bg_elements[i].w, &bg_elements[i].h) != 4) {
            fprintf(stderr, "Error reading file\n");
            free(bg_elements);
            fclose(file1);
            return EXIT_FAILURE;
        }
    }

    fclose(file1);



    //---------------------------LOAD GROUND FROM TXT------------------------------
    FILE *file2 = fopen("map/ground.txt", "r");
    if (file2 == NULL) {
        perror("Failed to open file");
        free(bg_elements);
        return EXIT_FAILURE;
    }

    // Compter le nombre de lignes dans ground.txt
    int nb_sol = count_lines_in_file(file2);

    // Allocation dynamique de la mémoire pour ground_elements
    SDL_Rect *ground_elements = (SDL_Rect *)malloc(nb_sol * sizeof(SDL_Rect));
    if (ground_elements == NULL) {
        perror("Failed to allocate memory");
        free(bg_elements);
        fclose(file2);
        return EXIT_FAILURE;
    }

    // Lire les données dans ground_elements
    for (int i = 0; i < nb_sol; i++) {
        if (fscanf(file2, "%d,%d,%d,%d\n", &ground_elements[i].x, &ground_elements[i].y, &ground_elements[i].w, &ground_elements[i].h) != 4) {
            fprintf(stderr, "Error reading file\n");
            free(bg_elements);
            free(ground_elements); // Libération de la mémoire en cas d'erreur
            fclose(file2);
            return EXIT_FAILURE;
        }
    }
    fclose(file2);





    while (player.alive)
    {
        process_input(&player);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        SDL_RenderClear(rend);


        //-----------------------------PROCESS GOOMBAS--------------------------------
        for (int i =0; i < nb_goombas;i++){
            process_goomba(&goombas[i]);
            check_collision_goomba(&goombas[i],&player);

            goomba_rects[i].x = (int)(goombas[i].x_pos - camera_x);
            goomba_rects[i].y = (int)(goombas[i].y_pos);

        }


        //-----------------------------PROCESS PLAYER--------------------------------
        process_physics(&player,&camera_x, bg_elements, nb_blocks, ground_elements, nb_sol);
        

        player_rect.x = (int)(player.x_pos - camera_x);
        player_rect.y = (int)player.y_pos;
        
        player_hitbox.x = player_rect.x;
        player_hitbox.y = player_rect.y;

        //------------------------------DRAW BACKGROUNDS---------------------------
        int bg_width, bg_height;
        SDL_QueryTexture(bg_texture, NULL, NULL, &bg_width, &bg_height);
        for (int i = 0; i <= WIDTH / bg_width + 1; ++i)
        {
            SDL_Rect bg_rect = {
                i * bg_width - (int)camera_x % bg_width,
                0,
                bg_width,
                HEIGHT
            };
            SDL_RenderCopy(rend, bg_texture, NULL, &bg_rect);
        }

        //---------------------------DRAW BLOCKS-------------------------------
        for (int i = 0; i < nb_blocks; ++i)
        {
                SDL_Rect bg_rect = {
                    bg_elements[i].x - (int)camera_x,
                    bg_elements[i].y,
                    bg_elements[i].w,
                    bg_elements[i].h
                };
                SDL_RenderCopy(rend, decor_sprites[0], NULL, &bg_rect);
        }

        //----------------------------DRAW GROUNDS---------------------------

        for (int i = 0; i < nb_sol; ++i)
        {
                SDL_Rect sol_rect = {
                    ground_elements[i].x - (int)camera_x,
                    ground_elements[i].y,
                    ground_elements[i].w,
                    ground_elements[i].h
                };
                SDL_RenderCopy(rend, ground_texture, NULL, &sol_rect);
        }



        //-----------------------DRAW THE PLAYER-------------------------------

        if (player.x_vel > 0) {
            player.direction_faced = 0; //droite
            if (player.sprint){

            if (player.run_frame % 4  < 2) {
                SDL_RenderCopy(rend, mario_sprites[1], NULL, &player_rect);
            }
            else {
                SDL_RenderCopy(rend, mario_sprites[2], NULL, &player_rect);
            }

            }

            else {

            if (player.run_frame % 8  < 4) {
                SDL_RenderCopy(rend, mario_sprites[1], NULL, &player_rect);
            }
            else {
                SDL_RenderCopy(rend, mario_sprites[2], NULL, &player_rect);
            }
            }
            
            player.run_frame ++;
        }

        if (player.x_vel < 0)
        {
            player.direction_faced = 1; //gauche
            if (player.sprint){

            if (player.run_frame % 4  < 2) {
                SDL_RenderCopy(rend, mario_sprites[4], NULL, &player_rect);
            }
            else {
                SDL_RenderCopy(rend, mario_sprites[5], NULL, &player_rect);
            }

            }

            else {

            if (player.run_frame % 8  < 4) {
                SDL_RenderCopy(rend, mario_sprites[4], NULL, &player_rect);
            }
            else {
                SDL_RenderCopy(rend, mario_sprites[5], NULL, &player_rect);
            }
            }
            
            player.run_frame ++;
        }

        if (player.x_vel == 0) {
            if (!player.direction_faced){
                SDL_RenderCopy(rend, mario_sprites[0], NULL, &player_rect); //droite
            }
            else {
                SDL_RenderCopy(rend, mario_sprites[3], NULL, &player_rect); //gauche
            }
            
        }


        //---------------------------DRAW GOOMBAS----------------------------------

        for (int i= 0; i < nb_goombas; i++){
            if (goombas[i].alive)    
        {
        SDL_RenderCopy(rend, enemy_sprites[goombas[i].sprite], NULL, &goomba_rects[i]);
        }
        else{
            if (goombas[i].frame_counter_death < 30){
                SDL_RenderCopy(rend, enemy_sprites[goombas[i].sprite], NULL, &goomba_rects[i]);
            }
        }
        }



        //---------------------------DRAW WINDOWS----------------------------------
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / FPS);
    }
    //---------------------------DEALLOCAITON----------------------------------
    SDL_DestroyTexture(mario_sprites[0]);
    SDL_DestroyTexture(mario_sprites[1]);
    SDL_DestroyTexture(mario_sprites[2]);
    SDL_DestroyTexture(bg_texture);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    SDL_Quit();
    return 0;
}
