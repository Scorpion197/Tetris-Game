#include "const.h"
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>


/* a procedure to load blocks */ 
int **drawBlock( ArrayPositions positions, int **array, SDL_Surface *screen, int** screenArray);

/* a procedure to initialize the position of tetris blocks */

ArrayPositions returnPos();

/* a function containing the activated/deactivated boxes , it reads the type of the box from the file 
    ,stores the values in a 2D array and return the array */ 

int **activateBox();

/* a procedure to move the blocks */ 

void moveBlock( SDL_Surface *screen);
/* a procedure to clear the screen every time we draw a block */ 

void clearScreen(SDL_Surface *screen, ArrayPositions positions);

/* a procedure to rotate the blocks and return the array where of 0/1 which indicates the activated 
    / deactivated box */

int **rotateBlock(int **array);

/* a function to return the type of the box to load , choosen randomly */

int return_Block();

/* a boolean functions whech returns 1 if the current block reached the end of the screen,
    0 if not */

int reached(ArrayPositions positions, int** array, int**wholeScreen);

int **initScreen();


