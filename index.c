#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//-----------------------------------------------------------------------------//
// Constante
#define BOARDWIDTH 40
#define BOARDHEIGHT 40


//-----------------------------------------------------------------------------//
// Structure

// Struc du snake
typedef struct
{
    int x, y;
} Snake;

// Struc du jeu
typedef struct
{
    Snake snake[BOARDWIDTH * BOARDHEIGHT];
    int size;
    int foodX, foodY;
    int score;
} Game;

//-----------------------------------------------------------------------------//