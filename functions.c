#include <string.h>
#include "const.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

int **initScreen()
{
    int **wholeScreen;
    int i, j; 

    wholeScreen = malloc (sizeof(int *) * NUMBER_VERTICAL_BOXES);

    if ( wholeScreen == NULL)
    {
        fprintf(stderr, "Error while allocating space (initScreen function) %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    for ( i = 0; i < NUMBER_VERTICAL_BOXES; i++)
    {
        wholeScreen[i] = malloc(sizeof(int*)* NUMBER_HORIZONTAL_BOXES);

        if (wholeScreen[i] == NULL)
        {

            fprintf(stderr, "Error while allocating space (initScreen function) %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }

    for ( i = 0; i < NUMBER_VERTICAL_BOXES; i++)
    {
        for ( j = 0; j < NUMBER_HORIZONTAL_BOXES; j++)
            wholeScreen[i][j] = 0; 
    }



    return wholeScreen;
}

void clearScreen(SDL_Surface *screen, ArrayPositions positions)
{
    SDL_Rect position;
    SDL_Surface *lines[700] = {NULL}, *box = NULL;
    int activateLine, activateColumn;
    int i, j;
    position.x = 20;

    box = SDL_CreateRGBSurface(SDL_HWSURFACE,DIMENSIONS, DIMENSIONS, 32, 0, 0, 0, 0);
	SDL_FillRect(box, NULL, SDL_MapRGB(screen->format,255, 0, 0));


    for ( i = 0 ; i < 700; i++)
        lines[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, LINE_WIDTH, LINE_HEIGHT, 32, 0, 0, 0, 0);
    
    /* creating lines horizontaly */ 

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    for ( i = 0; i < 30 ; i++)
    {
        for (j = 0; j < 700; j++)
        {
            position.y = j;

            SDL_FillRect(lines[j],NULL,SDL_MapRGB(screen->format,1,1,1));
            SDL_BlitSurface(lines[j], NULL, screen, &position);
        }
        position.x = position.x + 20;
    }

    /*Creating lines vertically */
    position.y = 20; 

    for ( i = 0; i < 35; i++)
    {
        for ( j = 0; j < 600; j++)
        {
            position.x = j;

            SDL_FillRect(lines[j],NULL,SDL_MapRGB(screen->format,1,1,1));
            SDL_BlitSurface(lines[j], NULL, screen, &position);
            
        }

        position.y = position.y + 20;
    }


    for (i = 0; i < 700; i++)
        SDL_FreeSurface(lines[i]);

}

int return_Block()
{
    time_t t;
    int typeBox; 

    srand((unsigned) time(&t));
    typeBox = rand() % 5;

    if (typeBox == L)
        return L; 
    else if (typeBox == I )
        return I; 
    else if (typeBox == O)
        return O;
    else if (typeBox == T)
        return T;
    else if (typeBox == S)
        return S;
    

}
ArrayPositions returnPos()
{
    ArrayPositions locations;
    int x, y; /*Initial positions */
    int i, j;

    y = 80;  
    
    for ( i = 0; i < NUMBER_LINES; i++)
    {
         x = 80; 
        for ( j = 0; j < NUMBER_LINES; j++)
        {
            locations.arrayPos[i][j].x = x;
            locations.arrayPos[i][j].y = y;
            x = x + 20;
        }

        y = y + 20 ;
    }

    return locations;
}

int **drawBlock( ArrayPositions boxPosition, int **array, SDL_Surface *screen,int **screenArray)
{
    SDL_Surface *blocks = NULL;
    SDL_Rect position;
    int activateColumn, activateLine;
    int i, j, k; 
    int blockColor, blockColor1, blockColor2; /* The color of the blocks */
    time_t t;
    int delete; /* boolean variable used in deleting lines */


    srand((unsigned) time(&t));

    blocks = SDL_CreateRGBSurface(SDL_HWSURFACE, DIMENSIONS, DIMENSIONS, 32, 0, 0, 0, 0);
    SDL_FillRect(blocks, NULL, SDL_MapRGB(blocks->format, blockColor, blockColor1, blockColor2));

    /* get the position of the current moving activated block from the boolean 4*4 array and set it to
     1 in the screen array */ 

    for ( i = 0; i < NUMBER_LINES; i++)
    {
        for ( j = 0; j < NUMBER_LINES; j++)
        {
            if (array[i][j] == 1)
            {

                activateLine = boxPosition.arrayPos[i][j].y / 20;
                activateColumn = boxPosition.arrayPos[i][j].x / 20;
                screenArray[activateLine][activateColumn] = 1; 
            }
        }
    }

    /* treating the case where the box has reached the end of the screen ,which need to be displayed 
        always */

    if (reached(boxPosition, array,screenArray) == 1 )
    {
        blockColor = rand() % 266; blockColor1 = rand() % 266; blockColor2 = rand() % 266;

        for ( i = 0; i < NUMBER_LINES; i++)
        {
            for ( j = 0; j < NUMBER_LINES; j++)
            {
                if (array[i][j] == 1)
                {
                    activateLine = boxPosition.arrayPos[i][j].y / 20; 
                    activateColumn= boxPosition.arrayPos[i][j].x / 20; 
                    screenArray[activateLine][activateColumn] = 2;

                }
            }
        }
    }

    /* Deleting lines and increment the score */ 

    i = 32;
    while (i > 0)
    {
        j = 0; 
        delete = 1;
        while ((j < NUMBER_HORIZONTAL_BOXES) && (delete))
        {
            if (screenArray[i][j] != 2)
                delete = 0; 
            else 
                j++;                
        }

        if (delete == 1)
        {

            for ( k = 0; k < i - 1; k++)
            {
                for ( j = 0; j < NUMBER_HORIZONTAL_BOXES; j++)
                {
                    screenArray[k][j] = screenArray[k+1][j];
                }
            } 
        }
        i--;
    }

      

    /* displaying activated cases which are whether now activated(contains 1) or are always activated ( contains 2) */
    for ( i = 0 ; i < NUMBER_VERTICAL_BOXES; i++)
    {
        for ( j = 0; j < NUMBER_HORIZONTAL_BOXES; j++)
        {
            if ((screenArray[i][j] == 1) || (screenArray[i][j] == 2))
            {
                position.x = j * 20; 
                position.y = i * 20; 
                SDL_BlitSurface(blocks, NULL, screen, &position);
                if (screenArray[i][j] != 2)
                    screenArray[i][j] = 0;
            }
        }
    }

    SDL_Flip(screen);


    SDL_FreeSurface(blocks);
    return screenArray;
}

int **activateBox()
{
    FILE *file = NULL; 
    size_t size = 40; /* 100 characters in a single line */ 
    char *string; 
    int **states; /* stores 1 and 0 values depending on the state of the box whether it's activated 
                    or not */
    int i, j ;
    int typeBox = return_Block();

    if ( typeBox == L )
        file = fopen("L.txt", "r");
    else if ( typeBox == S )
        file = fopen("S.txt", "r");
    else if ( typeBox == I )
        file = fopen("I.txt", "r");
    else if( typeBox == T )
        file = fopen("T.txt", "r");
    else if ( typeBox == O )
     
    file = fopen("O.txt", "r");
    
    /* read the file where we stocked the state of the boxes, and store it in 4*4 array */
    if ( file == NULL)
    {
        fprintf(stderr, "error while opening the file%s\n ", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    else 
    {
        states =  malloc (sizeof(int *) * NUMBER_LINES);

        if (states == NULL)
        {
            fprintf(stderr, "error while allocating space%s\n ", SDL_GetError());
            exit(EXIT_FAILURE);
        }


        for ( i = 0; i < NUMBER_LINES ; i++)
        {
            states[i] = malloc(sizeof(int*)* NUMBER_LINES);

            if (states[i] == NULL)
            {
                fprintf(stderr, "error while allocating space%s\n ", SDL_GetError());
                exit(EXIT_FAILURE);
            }
        }
                
        string = malloc(size);
        i = 0 ;
        while(getline(&string, &size , file) != -1)
        {
            sscanf(string, "%d %d %d %d", &states[i][0], &states[i][1], &states[i][2], &states[i][3]); 
            i++;
        }
    }

    fclose(file);

    return states;
}

int **rotateBlock(int **array)
{

    int **newStates; 
    int i, j; 
    int lines, columns;

    newStates = malloc (sizeof(int *) * NUMBER_LINES);

    if (newStates == NULL)
    {
        fprintf(stderr, "Error while allocating space (rotateBlock) %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    for ( i = 0; i < NUMBER_LINES; i++)
    {
        newStates[i] = malloc(sizeof(int*)* NUMBER_LINES);

        if (newStates[i] == NULL)
        {
            fprintf(stderr, "Error while allocating space %s\n", SDL_GetError()); 
            exit(EXIT_FAILURE);
        }
    }


    columns = 3; 
    for ( i = 0; i < NUMBER_LINES; i++)
    {
        lines = 0;
        for ( j = 0; j < NUMBER_LINES; j++)
        {
            newStates[lines][columns] = array[i][j];
            lines++;
        }

        columns--;
    }

    return newStates;
}


void moveBlock( SDL_Surface *screen)
{
    SDL_Event event; 
    int continuer = 1;
    int i, j;
    ArrayPositions tempPositions = returnPos();
    int **rotatedArray = activateBox(); 
    int **screenArray = initScreen();
    int **wholescreen;

    SDL_EnableKeyRepeat(80, 80);
    while ( continuer )
    {
        wholescreen = drawBlock(tempPositions, rotatedArray, screen, screenArray);
        SDL_Flip(screen);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0; 
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0; 
                        break; 
                    case SDLK_DOWN:
                     if (reached(tempPositions, rotatedArray,wholescreen) == 0)
                        {
                            for ( i = 0; i < NUMBER_LINES; i++)
                            {
                                for ( j = 0; j < NUMBER_LINES; j++)
                                    tempPositions.arrayPos[i][j].y = tempPositions.arrayPos[i][j].y + 20;
                            }
                        }

                        else 
                        {
                            clearScreen(screen, tempPositions);
                            tempPositions = returnPos();
                            rotatedArray = activateBox();
                        }

                        break;
                    case SDLK_UP:
                        for ( i = 0; i < NUMBER_LINES; i++)
                        {
                            for ( j = 0; j < NUMBER_LINES; j++)
                                tempPositions.arrayPos[i][j].y = tempPositions.arrayPos[i][j].y - 20;
                        }
                        break;
                    case SDLK_RIGHT:
                        for ( i = 0; i < NUMBER_LINES; i++)
                        {
                            for ( j = 0; j < NUMBER_LINES; j++)
                                tempPositions.arrayPos[i][j].x = tempPositions.arrayPos[i][j].x + 20;
                        }
            
                        break;
                    case SDLK_LEFT:
                        for ( i = 0; i < NUMBER_LINES; i++)
                        {
                            for ( j = 0; j < NUMBER_LINES; j++)
                                tempPositions.arrayPos[i][j].x = tempPositions.arrayPos[i][j].x - 20;
                        }
            
                        break;
                    
                    /* press on 'r' to rotate the block */ 
                    case SDLK_r:
                        rotatedArray = rotateBlock(rotatedArray);
                        break; 
                    default:
                        break;
                }
                clearScreen(screen, tempPositions);
                drawBlock(tempPositions, rotatedArray, screen,screenArray); 
        }

    }


}

int reached(ArrayPositions positions, int **array, int**wholeScreen)
{
    int i, j;
    SDL_Rect position; 
    int continuer = 1;
    int activateLine, activateColumn;


    i = 0;
    while ((i < NUMBER_LINES) && (continuer))
    {
        j = 0; 
        while (( j < NUMBER_LINES) && (continuer))
        {

            activateLine = positions.arrayPos[i][j].y  / 20;
            activateColumn = positions.arrayPos[i][j].x / 20; 

            if ((positions.arrayPos[i][j].y + 20  == 660 ) && ( array[i][j] == 1)) /* 660 is the height of the screen */ 
            {
                continuer = 0; 
                return 1;
            }

            else if (( wholeScreen[activateLine + 1][activateColumn] == 2) && (array[i][j] == 1))
            {
                continuer = 0; 
                return 1;
            }

            else 
                j++; 
        }

        i++;
    }


    if (i == NUMBER_LINES)
        return 0;
}
