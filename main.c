#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "pakuman.h"
#include "gestionGraphique.h"
#include "fantome.h"
#include "plateau.h"
#include "constants.h"

int score = 0;

// Function to check collision between Pakuman and ghosts
int check_collision(struct Pakuman pakuman, struct Fantome fantome)
{
    // Calculate the sides of the rectangles
    int left1 = pakuman.posX;
    int right1 = pakuman.posX + PAKUMAN_WIDTH;
    int top1 = pakuman.posY;
    int bottom1 = pakuman.posY + PAKUMAN_HEIGHT;

    int left2 = fantome.posX;
    int right2 = fantome.posX + GHOST_WIDTH;
    int top2 = fantome.posY;
    int bottom2 = fantome.posY + GHOST_HEIGHT;

    // Check for collision
    if (bottom1 < top2 || top1 > bottom2 || right1 < left2 || left1 > right2)
    {
        // No collision
        return 0;
    }
    else
    {

        // Collision detected
        return 1;
    }
}

int main(int argc, char **argv)
{
    int nbrmanges = 0;
    int ghostEaten = 0;

    // création du plateau
    int map[MAP_HEIGHT][MAP_WIDTH];
    Init_Map(map);

    // création de la window
    initSDL();
    TTF_Init();
    SDL_Init(SDL_INIT_AUDIO);


    SDL_Window *win = createWindow("Aljman", SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Renderer *ren = createRenderer(win);
    SDL_Event event;

    // création du fantome
    struct Fantome fantome;
    struct Fantome fantome1;
    struct Fantome fantome2;
    struct Fantome fantome3;

    Init_Fantome(&fantome, 250, 250, '1');
    Init_Fantome(&fantome1, 710, 50, '2');
    Init_Fantome(&fantome2, 50, 770, '3');
    Init_Fantome(&fantome3, 710, 770, '4');

    // affichage du fantome
    Afficher_Fantome(fantome, win, ren);

    // création et affichage du personnage
    struct Pakuman pakuman;
    Init_Pakuman(&pakuman);

    Afficher_Pakuman(pakuman, win, ren);

    // textures/resources à utiliser
    SDL_Texture *game_over_texture = loadTexture("sprites/game_over.bmp", ren);
    SDL_Texture *you_win = loadTexture("sprites/VSwin.bmp", ren);
    SDL_Texture *wall_texture = loadTexture("sprites/wall.bmp", ren);
    SDL_Texture *gum_texture = loadTexture("sprites/gum.bmp", ren);
    SDL_Texture *bigGum_texture = loadTexture("sprites/bigGum.bmp", ren);
    SDL_Texture *cherry_texture = loadTexture("sprites/cherry.bmp", ren);
    SDL_Texture *TP1_texture = loadTexture("sprites/TP1.bmp", ren);
    SDL_Texture *TP2_texture = loadTexture("sprites/TP2.bmp", ren);

    TTF_Font *scoreFont = TTF_OpenFont("./fonts/Minecraft.ttf", SCORE_FONT_SIZE);
    SDL_Color scoreColor = {255, 255, 255};

    // main game loop
    int is_game_over = 0;
    int is_quit = 0;

    while ((!is_quit) && (!is_game_over))
    {
        char d;

        int f_start = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                is_quit = 1;
            }
            determine_direction(event, &pakuman);
        }

        SDL_RenderClear(ren);

        // display the map
        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                int tile_type = map[i][j];
                // Determine texture based on tile type
                SDL_Texture *tile_texture = NULL;
                switch (tile_type)
                {
                case 0:
                    // Empty tile
                    break;
                case 1:
                    // Wall
                    tile_texture = wall_texture;
                    break;
                case 2:
                    // Gum
                    tile_texture = gum_texture;
                    break;
                case 3:
                    // Big Gum
                    tile_texture = bigGum_texture;
                    ;
                    break;
                case 4:
                    tile_texture = cherry_texture;
                    break;
                case 5:
                    tile_texture = TP1_texture;
                    break;
                case 6:
                    tile_texture = TP2_texture;
                    break;
                }
                if (tile_texture != NULL)
                {
                    // Load and render texture

                    SDL_Rect dst = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                    SDL_RenderCopy(ren, tile_texture, NULL, &dst);
                }
            }
        }

        // Render et deplacer le fantome
        if (fantome.mange == 0)
        {
            Deplacer_Fantome(&fantome, win, ren, map);
        }
        if (fantome1.mange == 0)
        {
            Deplacer_Fantome(&fantome1, win, ren, map);
        }
        if (fantome2.mange == 0)
        {
            Deplacer_Fantome(&fantome2, win, ren, map);
        }
        if (fantome3.mange == 0)
        {
            Deplacer_Fantome(&fantome3, win, ren, map);
        }

        // deplacer le pakuman
        Deplacer_Pakuman(&pakuman, win, ren, map, &score);

        if (check_collision(pakuman, fantome)  ||
            check_collision(pakuman, fantome1) ||
            check_collision(pakuman, fantome2) ||
            check_collision(pakuman, fantome3))
        {

            if (pakuman.peutmanger == 0)
            {
                pakuman.nbrvies--;
                pakuman.posX = INITIAL_PAKUMAN_X;
                pakuman.posY = INITIAL_PAKUMAN_Y;
            }
            else
            {
                if (check_collision(pakuman, fantome) && !fantome.mange)
                {
                    fantome.mange = 1;
                    ghostEaten = 1;
                }
                if (check_collision(pakuman, fantome1) && !fantome1.mange)
                {
                    fantome1.mange = 1;
                    ghostEaten = 1;
                }
                if (check_collision(pakuman, fantome2) && !fantome2.mange)
                {
                    fantome2.mange = 1;
                    ghostEaten = 1;
                }
                if (check_collision(pakuman, fantome3) && !fantome3.mange)
                {
                    fantome3.mange = 1;
                    ghostEaten = 1;
                }
            }
        }

        // update mange counter
        nbrmanges += ghostEaten;
        ghostEaten = 0;

        if (360 <= pakuman.posX && 400 >= pakuman.posX)
        {
            if (400 <= pakuman.posY && 440 >= pakuman.posY)
            {
                pakuman.posX = 40;
                pakuman.posY = 40;
            }
        }

        // display score in middle left
        char scoreText[15];
        snprintf(scoreText, sizeof(scoreText), "%d", score);

        SDL_Surface *scoreTextSurface = TTF_RenderText_Solid(scoreFont, "Score Actuel : ", scoreColor);
        SDL_Texture *scoreTextTexture = SDL_CreateTextureFromSurface(ren, scoreTextSurface);

        SDL_Surface *scoreNumSurface = TTF_RenderText_Solid(scoreFont, scoreText, scoreColor);
        SDL_Texture *scoreNumTexture = SDL_CreateTextureFromSurface(ren, scoreNumSurface);

        renderTexture(scoreTextTexture, ren, 5, 380, 150, 50);
        renderTexture(scoreNumTexture, ren, 40, 430, 50, 50);

        // SDL_RenderCopy(ren, Message, NULL, &scoreRect);

        // SDL_FreeSurface(surfaceMessage);
        // SDL_DestroyTexture(Message);

        updateDisplay(ren);

        // handle game ending logic
        if (pakuman.nbrvies == 0)
        {

            is_game_over = 1;
            SDL_RenderClear(ren);
            SDL_Rect dst = {0, 0, 760, 840};
            SDL_RenderCopy(ren, game_over_texture, NULL, &dst);
            updateDisplay(ren);
            SDL_Delay(3000);

            break;
        }
        if (score >= 1410)
        {
            is_game_over = 1;
            SDL_RenderClear(ren);
            SDL_Rect dst = {0, 0, 760, 840};
            SDL_RenderCopy(ren, you_win, NULL, &dst);
            updateDisplay(ren);
            SDL_Delay(3000);

            break;
        }

        //wait enough time to match desired frame rate
        int f_end = SDL_GetTicks();
        if (FRAME_DELAY - (f_end - f_start) > 0){
            SDL_Delay(FRAME_DELAY - (f_end - f_start));
        }

        int f_real_end = SDL_GetTicks();
        printf("Current FPS : %d \n", 1000/(f_real_end - f_start));

    }

    printf("Score : %d\n", score);

    return 0;
}
