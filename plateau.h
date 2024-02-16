#ifndef PLATEAU_H_
#define PLATEAU_H_

#include <SDL2/SDL.h>
#define MAP_HEIGHT 21
#define MAP_WIDTH 19
#define PWIDTH 50
#define PHEIGHT 50
#define TILE_SIZE 40

int allEqual(int arr[MAP_HEIGHT][MAP_WIDTH], int value);

void Init_Map(int map[MAP_HEIGHT][MAP_WIDTH]);

void Draw_Map();

#endif
