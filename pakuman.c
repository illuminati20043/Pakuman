#include "pakuman.h"
#include "plateau.h"

//initialisation du pacman
*gumCount = 0;
// Function to check collision with walls
int check_collision_wall(struct Pakuman pakuman, int map[MAP_HEIGHT][MAP_WIDTH]) {
    // Calculate the tile indices of the Pakuman's position
    int tileX = pakuman.posX / TILE_SIZE;
    int tileY = pakuman.posY / TILE_SIZE;
    
    // Check if the tile at Pakuman's position is a wall
    if (map[tileY][tileX] == 1) {
        // Collision detected with wall
        return 1;
    } else {
        // No collision with wall
        return 0;
    }
}

void Init_Pakuman(struct Pakuman *pakuman)
{
	//3 vies à avoir
	pakuman->nbrvies = 3;
	
	//positions 2d
	pakuman->posX = 40;
	pakuman->posY = 40;
	
	pakuman->direction = 'd';
    pakuman->peutmanger=0;
	



}



void Afficher_Pakuman(struct Pakuman pakuman,SDL_Window* win,SDL_Renderer * ren)
{
	//création d'une image à utiliser
	SDL_Texture* monImage = loadTexture("pakuman_0.bmp",ren);
	SDL_Rect dst = {pakuman.posX,pakuman.posY,36,36};
	SDL_RenderCopy(ren, monImage, NULL, &dst);
    	SDL_DestroyTexture(monImage); // Free the texture



}




void Deplacer_Pakuman(struct Pakuman *pakuman,SDL_Window* win,SDL_Renderer * ren,int map[MAP_HEIGHT][MAP_WIDTH],int *score)
	
{	





//on déplace selon la direction du pakuman

	 // Save the current position of the Pakuman
    int currentPosX = pakuman->posX;
    int currentPosY = pakuman->posY;

    // Move the Pakuman according to the direction
    int tileX = pakuman->posX / TILE_SIZE;
    int tileY = pakuman->posY / TILE_SIZE;
    
    switch (pakuman->direction) {
        case 'd':
            if (pakuman->posY + 5 +36< 840) {

                int nextTileY = (pakuman->posY + 5+30) / TILE_SIZE;
                if (map[nextTileY][tileX] != 1) {
                    pakuman->posY +=4;
                }
            }
            break;
        case 'u':
            if (pakuman->posY - 5 >= 0) {

                int nextTileY = (pakuman->posY - 5) / TILE_SIZE;
                if (map[nextTileY][tileX] != 1) {
                    pakuman->posY -= 4;
                }
            }
            break;
        case 'l':
            if (pakuman->posX - 5 >= 0) {
                int nextTileX = (pakuman->posX - 5) / TILE_SIZE;
                
                if (map[tileY][nextTileX] != 1) {
                    pakuman->posX -= 4;
                }
            }
            break;
        case 'r':
            if (pakuman->posX + 5 +36< 760) {
                int nextTileX = (pakuman->posX +5+30) / TILE_SIZE;

                if (map[tileY][nextTileX] != 1) {
                    pakuman->posX += 4;
                }
            }
            break;
    }
    	
	if (map[tileY][tileX] == 2 || map[tileY][tileX] == 3|| map[tileY][tileX] == 4) {
	if(map[tileY][tileX] == 2 ){*score+=10;*gumCount--;}
	else if(map[tileY][tileX] == 2 ) {*score+=100;*gumCount--;}
    else if(map[tileY][tileX] ==4)
    {pakuman->peutmanger =1;}
        map[tileY][tileX] = 0;
       

    }

	
	
	
	
	char alj[] = "pakuman_0.bmp";
	if(pakuman->direction=='d'){alj[8]='3';}
	else if(pakuman->direction=='u'){alj[8]='1';}
	else if(pakuman->direction=='l'){alj[8]='2';}
	else if(pakuman->direction=='r'){alj[8]='0';}
	
	
	SDL_Texture* monImage = loadTexture(alj,ren);
	
		SDL_Rect dst = {pakuman->posX,pakuman->posY,30,30};
		SDL_RenderCopy(ren, monImage, NULL, &dst);
	}
	
void determine_direction(SDL_Event Event,struct Pakuman*pakuman) {
    if (Event.type == SDL_KEYDOWN) {

        switch (Event.key.keysym.sym) {
        	
        	case SDLK_LEFT : 
        	if(pakuman->posX>0){
        		pakuman->direction = 'l';

        		}
        	break;
        
        	case SDLK_RIGHT : 
        	if(pakuman->posX<1000){
        		pakuman->direction = 'r';
        		
        		}
        	break;
        	
        	case SDLK_UP : 
        	if(pakuman->posY>0){
        		pakuman->direction = 'u';
        		
        		}

        	break;
        	
        	case SDLK_DOWN : 
        	if(pakuman->posY<1000){
        		pakuman->direction = 'd';

        		}
        	break;
        
        
        
        
        
        }
    }
}


	





