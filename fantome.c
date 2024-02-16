#include "fantome.h"



void Init_Fantome(struct Fantome *fantome,float X,float Y,char nombre){
    fantome->vie = 1;
    fantome ->posX = X;
    fantome ->posY = Y;
    fantome->direction = 'l';
    fantome->nbr = nombre;
    fantome->mange=0;//mangé et non pas manged


}




void Afficher_Fantome(struct Fantome fantome,SDL_Window* win,SDL_Renderer * ren)
{
	//création d'une image à utiliser
    char path[30];  
    snprintf(path, sizeof(path), "sprites/ghost%c_0.bmp", fantome.nbr);


	SDL_Texture* monImage = loadTexture(path,ren);
	SDL_Rect dst = {fantome.posX,fantome.posY,30,30};
	SDL_RenderCopy(ren, monImage, NULL, &dst);
    	SDL_DestroyTexture(monImage); // Free the texture



}



void Deplacer_Fantome(struct Fantome *fantome,SDL_Window* win,SDL_Renderer * ren, int map[MAP_HEIGHT][MAP_WIDTH]){


    //on déplace selon la direction du pakuman
    char test = fantome->direction;
        

    // Save the current position of the Fantome
    int currentPosX = fantome->posX;
    int currentPosY = fantome->posY;

    // Move the Fantome according to the direction
    int tileX = fantome->posX / TILE_SIZE;
    int tileY = fantome->posY / TILE_SIZE;


    switch (fantome->direction) {
        case 'd':
            if (fantome->posY + 5 < MAP_HEIGHT * TILE_SIZE) {
                int nextTileY = (fantome->posY + 36) / TILE_SIZE;
                if (map[nextTileY][tileX] != 1) {
                    fantome->posY += 5;
                }
                else{
                
                
            // If the next position is a wall, choose a new direction randomly
            switch (rand() % 4) { // Randomly choose a number between 0 and 3
                case 0:
                    fantome->direction = 'u'; // Up
                    break;
                case 1:
                    fantome->direction = 'd'; // Down
                    break;
                case 2:
                    fantome->direction = 'l'; // Left
                    break;
                case 3:
                    fantome->direction = 'r'; // Right
                    break;
            }
                
                
                }
            }
            break;
        case 'u':
            if (fantome->posY - 5 >= 0) {
                int nextTileY = (fantome->posY - 5) / TILE_SIZE;
                if (map[nextTileY][tileX] != 1) {
                    fantome->posY -= 5;
                }
                else{
                
                
            // If the next position is a wall, choose a new direction randomly
            switch (rand() % 4) { // Randomly choose a number between 0 and 3
                case 0:
                    fantome->direction = 'u'; // Up
                    break;
                case 1:
                    fantome->direction = 'd'; // Down
                    break;
                case 2:
                    fantome->direction = 'l'; // Left
                    break;
                case 3:
                    fantome->direction = 'r'; // Right
                    break;
            }
                
                
                }
            }
            break;
        case 'l':
            if (fantome->posX - 5 >= 0) {
                int nextTileX = (fantome->posX - 5) / TILE_SIZE;
                if (map[tileY][nextTileX] != 1) {
                    fantome->posX -= 5;
                }
                else{
                
                
            // If the next position is a wall, choose a new direction randomly
            switch (rand() % 4) { // Randomly choose a number between 0 and 3
                case 0:
                    fantome->direction = 'u'; // Up
                    break;
                case 1:
                    fantome->direction = 'd'; // Down
                    break;
                case 2:
                    fantome->direction = 'l'; // Left
                    break;
                case 3:
                    fantome->direction = 'r'; // Right
                    break;
            }
                
                
                }
            }
            break;
        case 'r':
            if (fantome->posX + 5 < MAP_WIDTH * TILE_SIZE) {
                int nextTileX = (fantome->posX + 36) / TILE_SIZE;
                if (map[tileY][nextTileX] != 1) {
                    fantome->posX += 5;
                }
                else{
                
                
            // If the next position is a wall, choose a new direction randomly
            switch (rand() % 4) { // Randomly choose a number between 0 and 3
                case 0:
                    fantome->direction = 'u'; // Up
                    break;
                case 1:
                    fantome->direction = 'd'; // Down
                    break;
                case 2:
                    fantome->direction = 'l'; // Left
                    break;
                case 3:
                    fantome->direction = 'r'; // Right
                    break;
            }
                
                
                }
            }
            break;
}

    int directionId;
	if(fantome->direction=='d'){directionId=3;}
	else if(fantome->direction=='u'){directionId=1;}
	else if(fantome->direction=='l'){directionId=2;}
	else if(fantome->direction=='r'){directionId=0;}
	
	char path[30];  
    snprintf(path, sizeof(path), "sprites/ghost%c_%d.bmp", fantome->nbr, directionId);


	
	
	SDL_Texture* monImage = loadTexture(path,ren);
	
		SDL_Rect dst = {fantome->posX,fantome->posY,30,30};
		SDL_RenderCopy(ren, monImage, NULL, &dst);










}
