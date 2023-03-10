#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//-----------------------------------------------------------------------------//
// Constantes
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
// Init du jeu

void gameInit(Game *game)
{
  game->size = 1;
  game->snake[0].x = BOARDWIDTH / 2;
  game->snake[0].y = BOARDHEIGHT / 2;
  game->foodX = rand() % BOARDWIDTH;
  game->foodY = rand() % BOARDHEIGHT;
  game->score = 0;
}

//-----------------------------------------------------------------------------//
