#include "s21_tetris.h"

const Figure SamplesFigure[] = {{.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 1, 1},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 1, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 0, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 1, 0, 0},
                                         {0, 1, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},

                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},
                                {.samples =
                                     {
                                         {0, 0, 0, 0, 0},
                                         {0, 1, 1, 0, 0},
                                         {0, 0, 1, 1, 0},
                                         {0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0},
                                     },
                                 .width = 5,
                                 .row = 0,
                                 .col = 0},
                                {.samples =
                                     {
                                         {0, 0, 0, 0},
                                         {0, 1, 1, 0},
                                         {0, 1, 1, 0},
                                         {0, 0, 0, 0},
                                     },
                                 .width = 4,
                                 .row = 0,
                                 .col = 0}};

Figure CaptureFigure(Figure figure) {  // взятие фигуры (А если утечка?)
  // Figure NewFigure = figure;
  // NewFigure.width = figure.width;
  // NewFigure.row = figure.row;
  // NewFigure.col = figure.col;
  // for (int i = 0; i < figure.width; i++) {
  //   for (int j = 0; j < figure.width; j++) {
  //     NewFigure.samples[i][j] = figure.samples[i][j];
  //   }
  // }
  return figure;
}

void LoadGame(int *score) {
  FILE *file = fopen("savegame.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", score);
    fclose(file);
  }
}

void SaveGame(int score, int maxScore) {
  FILE *file = fopen("savegame.txt", "w");
  if (file != NULL) {
    if (maxScore < score) {
      maxScore = score;
    }
    fprintf(file, "%d", maxScore);
    fclose(file);
  }
}

// void PrintBuffer(char buffer[ROWS][COLS], int rows, int cols) {
//   for (int i = 0; i < rows; i++) {
//     for (int j = 0; j < cols; j++) {
//       printw("%c ", buffer[i][j]);
//     }
//     printw("\n");
//   }
// }

void PrintTable(char Table[ROWS][COLS], int *score, Figure CurrentFigure,
                int maxScore) {
  char Buffer[ROWS][COLS] = {0};
  // Это для того, чтобы обновлялась позиция фигуры
  for (int i = 0; i < CurrentFigure.width; i++) {
    for (int j = 0; j < CurrentFigure.width; j++) {
      if (CurrentFigure.samples[i][j]) {
        Buffer[CurrentFigure.row + i][CurrentFigure.col + j] =
            CurrentFigure.samples[i][j];
        printf("CurrentFigure.row: %d\n", CurrentFigure.row);
        printf("CurrentFigure.col: %d\n", CurrentFigure.col);
        printf("i: %d\n", i);
        printf("j: %d\n", j);
      }
    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      printf("%c ", (Table[i][j] + Buffer[i][j]) ? 'O' : '.');
    }
    printf("\n");
  }

  clear();
  refresh();
  // printf("\n0\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      // printf("CurrentFigure.row: %d\n", CurrentFigure.row);
      // printw("%c ", (Table[i][j] + Buffer[i][j]) ? 'O' : '.');
      (Table[i][j] + Buffer[i][j]) ? color_figure() : printw("%c ", '.');
      // printf("\n1\n");
      /////////////////////////////Здесь ошибка памяти возникает
    }
    printw("\n");
  }
  AdditionalInformation(*score, maxScore);

  refresh();
}

int CheckRuleS(Figure TempFigure, char Table[ROWS][COLS]) {
  int flag = 1;  // okv

  // if (TempFigure.row > ROWS - 1) {
  //   flag = 0;
  // }
  for (int i = 0; i < TempFigure.width; i++) {
    for (int j = 0; j < TempFigure.width; j++) {
      if (Table[TempFigure.row + i + 1][TempFigure.col + j] &&
          TempFigure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}
int CheckRuleD(char Table[ROWS][COLS], Figure figure) {
  int flag = 1;  // ok

  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      if (figure.col + j >= COLS - 1 || figure.row + 1 > ROWS - 1) {
        if (figure.samples[i][j]) flag = 0;
      } else if (Table[figure.row + i + 1][figure.col + j + 1] &&
                 figure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}
int CheckRuleA(char Table[ROWS][COLS], Figure figure) {
  int flag = 1;  // ok

  // figure.col + figure.width > COLS || figure.row + figure.height > ROWS
  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      // if (figure.col + j <= 0 || figure.row + 1 > ROWS - 1) {
      if (figure.col + j <= 0 || figure.col + j - 1 >= COLS ||
          figure.row + i >= ROWS) {
        if (figure.samples[i][j]) flag = 0;
      } else if (Table[figure.row + i + 1][figure.col + j - 1] &&
                 figure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}

int CheckRuleW(char Table[ROWS][COLS], Figure figure) {
  int flag = 1;  // ok
  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      if (figure.col + j <= 0 || figure.row >= ROWS ||
          figure.col + j > COLS || figure.col + j >= COLS) {
        if (figure.samples[i][j]) flag = 0;
      } else if (Table[figure.row + i + 1][figure.col + j] &&
                 figure.samples[i][j])
        flag = 0;
    }
  }
  return flag;
}

void WriteToTable(Figure *CurrentFigure, char Table[ROWS][COLS]) {
  for (int i = 0; i < CurrentFigure->width; i++) {
    for (int j = 0; j < CurrentFigure->width; j++) {
      if (CurrentFigure->samples[i][j])
        Table[CurrentFigure->row + i][CurrentFigure->col + j] =
            CurrentFigure->samples[i][j];
    }
  }
}

Figure Rotate(Figure TempFigure) {
  Figure temp = CaptureFigure(TempFigure);
  for (int i = 0; i < TempFigure.width; i++) {
    for (int j = 0, k = TempFigure.width - 1; j < TempFigure.width; j++, k--) {
      TempFigure.samples[i][j] = temp.samples[k][i];
    }
  }
  return TempFigure;
}

void DeleteString(char Table[ROWS][COLS], int *score) {  // checks lines
  int sum, count = 0;
  for (int i = 0; i < ROWS; i++) {
    sum = 0;
    for (int j = 0; j < COLS; j++) {
      sum += Table[i][j];
    }

    if (sum == COLS) {
      count++;
      int k;
      for (k = i; k >= 1; k--)
        for (int l = 0; l < COLS; l++) Table[k][l] = Table[k - 1][l];

      for (int l = 0; l < COLS; l++) Table[k][l] = 0;
      (*score) += 100 * count;
    }
  }
}

int isRoof(Figure shape, char Table[ROWS][COLS]) {
  for (int i = 0; i < shape.width; i++) {
    for (int j = 0; j < shape.width; j++) {
      if (shape.row + i < Table[0][0]) {
        if (shape.samples[i][j]) return TRUE;
      }
    }
  }
  return FALSE;
}

void CreateFigure(Figure *CurrentFigure, char Table[ROWS][COLS], bool *GameOn) {
  WriteToTable(CurrentFigure, Table);
  // Figure NewFigure = SamplesFigure[rand() % 7];
  Figure NewFigure = SamplesFigure[0];
  NewFigure.row = -1;
  NewFigure.col = COLS / 4 + 1;
  *CurrentFigure = NewFigure;
  if (isRoof(*CurrentFigure, Table)) {
    (*GameOn) = FALSE;
  }
}

/*
int CheckCollision(Figure figure, int rowOffset, int colOffset,
                   char Table[ROWS][COLS]) {
  int flag = 1;  // ok
      int minRow = 0;
      int maxRow = 0;
      int minCol = 0;
      int maxCol = 0;

  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      minRow = figure.row + Table[i][j];
      maxRow = Table[i][j] + figure.width;
      minCol = figure.col + Table[i][j];
      maxCol = Table[i][j] + figure.width;
    }
  }

  if (maxRow > ROWS || minRow < 0 || maxCol > COLS || minCol < 0) {
    return 0;
  }

  for (int i = 0; i < figure.width; i++) {
    for (int j = 0; j < figure.width; j++) {
      if (figure.samples[i][j] && Table[minRow + i][minCol + j]) {
        flag = 0;
        break;
      }
    }
    if (!flag) {
      break;
    }
  }

  return flag;
}*/

void InputUser(int action, bool *GameOn, Figure *CurrentFigure,
               char Table[ROWS][COLS], int *score, int *Stop, int maxScore) {
  Figure TempFigure = *CurrentFigure;

  switch (action) {
    case 's':
      if (!(*Stop)) {
        TempFigure = *CurrentFigure;

        if (CheckRuleS(TempFigure, Table)) {
          TempFigure.row++;
        } else {
          CreateFigure(CurrentFigure, Table, GameOn);
          DeleteString(Table, score);
          TempFigure = *CurrentFigure;
        }
      }
      break;
    case 'd':
      if (CheckRuleD(Table, TempFigure) && !(*Stop)) {
        TempFigure.col++;
      }
      break;
    case 'a':
      if (CheckRuleA(Table, TempFigure) && !(*Stop)) {
        TempFigure.col--;
      }
      break;
    case 'w':
      if (CheckRuleW(Table, Rotate(TempFigure)) && !(*Stop) &&
          TempFigure.row >= 0) {
        TempFigure = Rotate(TempFigure);
      }
      break;
    case ' ':
      *Stop = !(*Stop);
      break;
    case 'o':
      *GameOn = FALSE;
      break;
  }
  *CurrentFigure = TempFigure;

  PrintTable(Table, score, *CurrentFigure, maxScore);
  // printf("\n4\n");
  // refresh();
}

int level(int score) {
  int count = 0;
  int level_up = 0;
  if (count <= 10) {
    level_up = (score / 600) * 100000;
    count++;
  }

  return level_up;
}