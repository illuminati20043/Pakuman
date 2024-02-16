#ifndef FANTOME_H
#define FANTOME_H

#include <stdio.h>
#include <stdlib.h>
#include "gestionGraphique.h"
#include "plateau.h"
struct Fantome
{
    int posX;
    int posY;
    int collisions;
    char direction;
    int vie;
    char nbr;
    int mange;
};

void Init_Fantome(struct Fantome *fantome, float X, float Y, char nombre);

void Afficher_Fantome(struct Fantome fantome, SDL_Window *win, SDL_Renderer *ren);

void Deplacer_Fantome(struct Fantome *fantome, SDL_Window *win, SDL_Renderer *ren, int map[MAP_HEIGHT][MAP_WIDTH]);

#endif
