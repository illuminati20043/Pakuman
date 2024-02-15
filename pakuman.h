#ifndef PAKUMAN_H
#define PAKUMA_H
#include <stdio.h>
#include <stdlib.h>
#include "gestionGraphique.h"
#include "plateau.h"
//structure du pakuman


extern int* gumCount;
struct Pakuman
{
	int nbrvies;
	int score;
	int is_gum;
	int is_collision;
	float posX;
	float posY;
	char direction;
	int peutmanger;
	


};




void Init_Pakuman(struct Pakuman *pakuman);

void Afficher_Pakuman(struct Pakuman pakuman,SDL_Window* win,SDL_Renderer * ren);	

void Deplacer_Pakuman(struct Pakuman *pakuman,SDL_Window* win,SDL_Renderer * ren,int map[MAP_HEIGHT][MAP_WIDTH],int *score);






void determine_direction(SDL_Event Event,struct Pakuman* pakuman);


#endif
