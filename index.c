#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

//-----------------------------------------------------------------------------//
// Constantes
#define VERSION "v0.1.5"
#define BOARDWIDTH 40
#define BOARDHEIGHT 20
#define WINDOWWIDTH 400
#define WINDOWHEIGHT 440
#define WINDOWPOSX 300
#define WINDOWPOSY 300

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

// Construit le board du jeu
void makeBoard(Game *game)
{
  system("cls");
  for (int index = 0; index < BOARDWIDTH + 2; index++)
  {
    printf("-");
  };
  printf("\n");
  for (int index = 0; index < BOARDHEIGHT; index++)
  {
    printf("|");
    for (int jindex = 0; jindex < BOARDWIDTH; jindex++)
    {
      int isSnake = 0;
      for (int kindex = 0; kindex < game->size; kindex++)
      {
        if (game->snake[kindex].x == jindex && game->snake[kindex].y == index)
        {
          printf("o");
          isSnake = 1;
        };
      }
      if (!isSnake && game->foodX == jindex && game->foodY == index)
      {
        printf("X");
      }
      else if (!isSnake)
      {
        printf(" ");
      }
    };
    printf("|\n");
  }
  for (int index = 0; index < BOARDWIDTH + 2; index++)
  {
    printf("-");
  }
  printf("\n");
  printf("Score: %d\n", game->score);
}

//-----------------------------------------------------------------------------//

// Controle du snake
void move(Game *game)
{
  for (int index = game->size - 1; index > 0; index--)
  {
    game->snake[index].x = game->snake[index - 1].x;
    game->snake[index].y = game->snake[index - 1].y;
  }
  switch (_getch())
  {
  case 'w':
    game->snake[0].y--;
    break;
  case 'a':
    game->snake[0].x--;
    break;
  case 's':
    game->snake[0].y++;
    break;
  case 'd':
    game->snake[0].x++;
    break;
  }
}

// Spawn pour la bouffe
void spawnFood(Game *game)
{
  game->foodX = rand() % BOARDWIDTH;
  game->foodY = rand() % BOARDHEIGHT;
}

// Check les collisions
int checkCollision(Game *game)
{
  // Bords du baord
  if (game->snake[0].x < 0 || game->snake[0].x >= BOARDWIDTH || game->snake[0].y < 0 || game->snake[0].y >= BOARDHEIGHT)
  {
    return 1;
  }

  // Avec le reste du snake
  for (int index = 1; index < game->size; index++)
  {
    if (game->snake[0].x == game->snake[index].x && game->snake[0].y == game->snake[index].y)
    {
      return 1;
    }
  }
  // Avec la bouffe
  if (game->snake[0].x == game->foodX && game->snake[0].y == game->foodY)
  {
    game->size++;
    game->score++;
    spawnFood(game);
  }
  return 0;
}

//-----------------------------------------------------------------------------//
// Loop du jeu pour play
void runGame()
{
  Game game;
  gameInit(&game);
  while (1)
  {
    makeBoard(&game);
    move(&game);
    if (checkCollision(&game))
    {
      printf("Game over!\n");
      break;
    }
    Sleep(50); // Ralenti le jeu
  }
}

// Lancement du Script
int main()
{
  // active la fenetre
  HWND hwnd = GetForegroundWindow();
  // Définir la position et la taille de la fenêtre (posX, posY, width, height)
  SetWindowPos(hwnd, HWND_TOPMOST, WINDOWPOSX, WINDOWPOSY, WINDOWWIDTH, WINDOWHEIGHT, SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);

  // Lock la taille de la window
  HWND consoleWindow = GetConsoleWindow();
  SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLongPtr(consoleWindow, GWL_STYLE) & ~WS_THICKFRAME);
  ShowScrollBar(consoleWindow, SB_BOTH, FALSE);

  // Set le nom de la fenetre 
  SetConsoleTitle("Little Snake Game by Niridor/Izae - ", VERSION);

  // Lance le jeu
  runGame();
  return 0;
}

//-----------------------------------------------------------------------------//

  //SetWindowPos(hwnd, HWND_TOPMOST, 300, 300, 400, 440, SWP_SHOWWINDOW);
  // Display la fenêtre
  //ShowWindow(hwnd, SW_SHOW);