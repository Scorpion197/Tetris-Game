#ifndef CONSTANTES 
#define CONSTANTES 
    
    #define WIDTH 600 /* which corresponds to 30 tiles horizontally*/
    #define HEIGHT 660  /* which corresponds to 33 tiles vertically */

    #define NUMBER_VERTICAL_BOXES 35
    #define NUMBER_HORIZONTAL_BOXES 30 

    #define LINE_HEIGHT 1
    #define LINE_WIDTH 1

    #define NUMBER_LINES 4
    #define NUMBER_COLUMNS 2

    #define DIMENSIONS 20  /* each box has 20 pixel in height, and width */

    /* we will give each tetris block */ 

    #define L 0 
    #define I 1 
    #define O 2 
    #define T 3 
    #define S 4

    /* defining the left, right, up and down arrows codes as they were defined in the standard */

    #define RIGHT_ARROW 275
    #define LEFT_ARROW 276
    #define UP_ARROW 273
    #define DOWN_ARROW 274 

    /* Define a record which contains the position of the boxes */ 

    typedef struct Position Position;
    struct Position
    {
        int x; 
        int y; 
        int state;
    };

    typedef struct ArrayPositions ArrayPositions;
    struct ArrayPositions
    {
        Position arrayPos[NUMBER_LINES][NUMBER_LINES];
    };

    

    /* Define the number of boxes in eaxh Block which is 4 */ 
    #define NUMBER_BOX 4


#endif