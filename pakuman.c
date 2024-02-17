#include "pakuman.h"
#include "plateau.h"

#include "constants.h"
#include "SDL2/SDL.h"

// initialisation du pacman
int *gumCount = 0;

SDL_AudioDeviceID audioID;

Uint32 eatWavLength;
Uint8 *eatWavBuffer;

Uint32 cherryWavLength;
Uint8 *cherryWavBuffer;

void Init_Pakuman(struct Pakuman *pakuman)
{
    // 3 vies à avoir
    pakuman->nbrvies = 3;

    // positions 2d
    pakuman->posX = 40;
    pakuman->posY = 40;

    pakuman->direction = 'd';
    pakuman->peutmanger = 0;

    // création/chargement sys audio
    if (eatWavLength == 0 || cherryWavLength == 0)
    {
        SDL_AudioSpec wavSpec;
        SDL_LoadWAV("sfx/pacman_chomp.wav", &wavSpec, &eatWavBuffer, &eatWavLength);
        SDL_LoadWAV("sfx/pacman_eatfruit.wav", NULL, &cherryWavBuffer, &cherryWavLength);

        audioID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    }
}

// checks collision with walls or boundaries
int check_collision_wall(int left, int right, int top, int bottom, int map[MAP_HEIGHT][MAP_WIDTH])
{
    // Get tile indices of all 4 edges for Pak
    int lIndex = left / TILE_SIZE;
    int rIndex = right / TILE_SIZE;

    int tIndex = top / TILE_SIZE;
    int bIndex = bottom / TILE_SIZE;

    // Check if the tile at input position is a wall
    if (map[tIndex][lIndex] == 1 ||
        map[tIndex][rIndex] == 1 ||
        map[bIndex][lIndex] == 1 ||
        map[bIndex][rIndex] == 1)
    {
        // wall collision
        return 1;
    }
    else if (left < 0 || right > SCREEN_WIDTH ||
             top < 0 || bottom > SCREEN_HEIGHT)
    {
        // edge collision
        return 2;
    }
    else
    {
        // no collision
        return 0;
    }
}

void Afficher_Pakuman(struct Pakuman pakuman, SDL_Window *win, SDL_Renderer *ren)
{
    // création d'une image à utiliser
    SDL_Texture *monImage = loadTexture("sprites/pakuman_0.bmp", ren);
    SDL_Rect dst = {pakuman.posX, pakuman.posY, 36, 36};
    SDL_RenderCopy(ren, monImage, NULL, &dst);
    SDL_DestroyTexture(monImage); // Free the texture
}

void Deplacer_Pakuman(struct Pakuman *pakuman, SDL_Window *win, SDL_Renderer *ren,
                      int map[MAP_HEIGHT][MAP_WIDTH], int *score)

{
    // Get the edges of pakuman's hitbox
    int left = pakuman->posX + HITBOX_BUFFER;
    int right = pakuman->posX + PAKUMAN_WIDTH - HITBOX_BUFFER;
    int top = pakuman->posY + HITBOX_BUFFER;
    int bottom = pakuman->posY + PAKUMAN_HEIGHT - HITBOX_BUFFER;

    int tileX = (left + right) / (2 * TILE_SIZE);
    int tileY = (top + bottom) / (2 * TILE_SIZE);

    // printf("%d  %d  \n", top, bottom);

    // handle pakuman movement
    switch (pakuman->direction)
    {
    case 'd':
        if (check_collision_wall(left, right, top + 5, bottom + 5, map) == 0)
        {
            pakuman->posY += 4;
        }
        break;
    case 'u':
        if (check_collision_wall(left, right, top - 5, bottom - 5, map) == 0)
        {
            pakuman->posY -= 4;
        }

        break;
    case 'l':
        if (check_collision_wall(left - 5, right - 5, top, bottom, map) == 0)
        {
            pakuman->posX -= 4;
        }
        break;
    case 'r':
        if (check_collision_wall(left + 5, right + 5, top, bottom, map) == 0)
        {
            pakuman->posX += 4;
        }
        break;
    }

    if (map[tileY][tileX] == 2 || map[tileY][tileX] == 3 || map[tileY][tileX] == 4)
{
   if (map[tileY][tileX] == 2) //small gum
{
    SDL_AudioStatus audioStatus = SDL_GetAudioDeviceStatus(audioID);
    *score += 10;
    *gumCount--;
    if (!(audioStatus == SDL_AUDIO_PLAYING)) {
        SDL_PauseAudioDevice(audioID, 0);
    }

    SDL_QueueAudio(audioID, eatWavBuffer, eatWavLength);
}
    else if (map[tileY][tileX] == 3) //big gum
    {
        *score += 100;
        *gumCount--;
    }
    else if (map[tileY][tileX] == 4) //powerup
    {
        pakuman->peutmanger = 1;
    }
        

        map[tileY][tileX] = 0;
    }
    else if(map[tileY][tileX] == 5){

        pakuman->posX = 40;
        pakuman->posY = 40;

    }

    // display corresponding sprite
    int directionId;
    if (pakuman->direction == 'd')
    {
        directionId = 3;
    }
    else if (pakuman->direction == 'u')
    {
        directionId = 1;
    }
    else if (pakuman->direction == 'l')
    {
        directionId = 2;
    }
    else if (pakuman->direction == 'r')
    {
        directionId = 0;
    }

    char alj[30];
    snprintf(alj, sizeof(alj), "sprites/pakuman_%d.bmp", directionId);

    SDL_Texture *monImage = loadTexture(alj, ren);

    SDL_Rect dst = {pakuman->posX, pakuman->posY, 30, 30};
    SDL_RenderCopy(ren, monImage, NULL, &dst);
}

void determine_direction(SDL_Event Event, struct Pakuman *pakuman)
{
    if (Event.type == SDL_KEYDOWN)
    {

        switch (Event.key.keysym.sym)
        {

        case SDLK_LEFT:
            if (pakuman->posX > 0)
            {
                pakuman->direction = 'l';
            }
            break;

        case SDLK_RIGHT:
            if (pakuman->posX < 1000)
            {
                pakuman->direction = 'r';
            }
            break;

        case SDLK_UP:
            if (pakuman->posY > 0)
            {
                pakuman->direction = 'u';
            }

            break;

        case SDLK_DOWN:
            if (pakuman->posY < 1000)
            {
                pakuman->direction = 'd';
            }
            break;
        }
    }
}
