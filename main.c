#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "const.h"
#include "functions.h"


int main(char argc, int *argv[]){

    SDL_Surface *screen = NULL , *image = NULL;
    SDL_Rect position;
    int i, j;
    int **merde = activateBox();


    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Tetris game ", NULL);

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        fprintf(stderr, "Error while initialiazing SDL %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    moveBlock(screen);


    for ( i = 0; i < NUMBER_LINES; i++)
        free(merde[i]);

    free(merde);



    SDL_Quit();



return EXIT_SUCCESS;
}


