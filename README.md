# Tetris Game 

This is a tetris game made with C language.
The main idea is to move a 4x4 array inside a large array which represents the screen of the game.
To load the game blocks i used files which contains 4x4 array of booleans which indicates the shape of the block. You can find 
them in the 'Blocks' folder.

# Compiling command 

If you are using linux then you can compile the game with the following command 

``` gcc -o main.exe main.c functions.c `sdl-config --libs` -lSDL_image ```

# Requirements 

* SDL 1.2 
