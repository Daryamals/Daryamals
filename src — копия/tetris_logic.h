#ifndef TETRIS_LOGIC_H
#define TETRIS_LOGIC_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define ROWS 20
#define COLS 11
#define TRUE 1
#define FALSE 0

char Table[ROWS][COLS] = {0};
int score = 0;
char GameOn = TRUE;
double timer = 500000;  // half second

typedef struct {
  char **array;
  int width, row, col;
} Shape;
// в этой структуре мы задали параметры для размера(width) фигуры,
// и его положение на экране(row, col) через двемерную матрицу
Shape current;

const Shape ShapesArray[7] = {
    {(char *[]){(char[]){0, 1, 1}, (char[]){1, 1, 0}, (char[]){0, 0, 0}},
     3},  // S_shape
    {(char *[]){(char[]){1, 1, 0}, (char[]){0, 1, 1}, (char[]){0, 0, 0}},
     3},  // Z_shape
    {(char *[]){(char[]){0, 1, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}},
     3},  // T_shape
    {(char *[]){(char[]){0, 0, 1}, (char[]){1, 1, 1}, (char[]){0, 0, 0}},
     3},  // L_shape
    {(char *[]){(char[]){1, 0, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}},
     3},                                              // ML_shape
    {(char *[]){(char[]){1, 1}, (char[]){1, 1}}, 2},  // SQ_shape
    {(char *[]){(char[]){0, 0, 0, 0}, (char[]){1, 1, 1, 1},
                (char[]){0, 0, 0, 0}, (char[]){0, 0, 0, 0}},
     4}  // R_shape
};  // прототипы всевозможных фигур для игры

// Прототипы функций
void initialize_game(TetrisGameState *game);
void update_game(TetrisGameState *game, int input);
void draw_game(const TetrisGameState *game);
int is_game_over(const TetrisGameState *game);

#endif  // TETRIS_LOGIC_H
