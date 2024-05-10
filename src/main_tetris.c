#include "s21_tetris.h"

extern const Figure SamplesFigure[];

int main() {
  srand(time(0));
  char Table[ROWS][COLS] = {0};
  int score = 0;
  int maxScore = 0;
  LoadGame(&maxScore);
  int Stop = 1;
  bool GameOn = TRUE;
  int action;
  struct timeval before, after;
  Figure CurrentFigure;
  initscr();              // для инициализации ncurses.
  nodelay(stdscr, TRUE);  // функция getch() не будет блокировать выполнение
  // программы, если нет ввода от пользователя. т.е. это установка режима
  // неожидания для окна stdscr
  start_color();
  CreateFigure(&CurrentFigure, Table, &GameOn);
  color_start();
  while (GameOn) {
    if ((action = getch()) != ERR) {
      InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
                maxScore);
    }
    // else {
    //   if (!Stop) {
    //     gettimeofday(&after, NULL);
    //     if (((double)after.tv_sec * 1000000 + (double)after.tv_usec) -
    //             ((double)before.tv_sec * 1000000 + (double)before.tv_usec) >
    //         500000 - level(score)) {
    //       action = 's';
    //       InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
    //                 maxScore);
    //       before = after;
    //     }
    //     if (action != ' ') {
    //       Pause_not();
    //     }
    //   }
    // }
  }
  color_over();
  SaveGame(score, maxScore);
  refresh();
  endwin();
  return 0;
}

// void PrintTable(char Table[ROWS][COLS], int *score, Figure CurrentFigure,
//                 int maxScore) {
//   char Buffer[ROWS][COLS] = {0};
//   // Это для того, чтобы обновлялась позиция фигуры
//   for (int i = 0; i < CurrentFigure.width; i++) {
//     for (int j = 0; j < CurrentFigure.width; j++) {
//       if (CurrentFigure.samples[i][j]) {
//         Buffer[CurrentFigure.row + i][CurrentFigure.col + j] =
//             CurrentFigure.samples[i][j];
//       }
//     }
//   }

//   clear();
//   refresh();

//   for (int i = 0; i < ROWS; i++) {
//     for (int j = 0; j < COLS; j++) {
//       if (Table[i][j] + Buffer[i][j]) {
//         printw("0");
//       } else
//         printw(".");
//     }
//     printf("\n");
//   }

//   maxScore = maxScore + 1;
//   *score = 9;
// }