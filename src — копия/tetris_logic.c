#include "tetris_logic.h"

#include <ncurses.h>
/*
    В этом файле должны быть реализованы основные механики игры, включая:

    1. Управление состоянием игры (текущие и следующие фигуры, счет, условие
   окончания игры)
    2. Логика движения и поворота фигур
    3. Система очистки линий и подсчета очков
    4. Прогрессирование игры (например, увеличение сложности)
*/

// Реализация функций логики игры
void initialize_game(TetrisGameState* game) {
  // Инициализация состояния игры
}

void update_game(TetrisGameState* game, int input) {
  // Обновление состояния игры на основе ввода
}
// Функция обновляет состояние игры на основе действий пользователя (например,
// движение фигуры влево, вправо, вниз, поворот) и автоматического движения
// фигуры вниз.

void draw_game(const TetrisGameState* game) {
  // Отрисовка состояния игры на экране
}
// Функция отвечает за отрисовку текущего состояния игры на экране,
// включая отображение фигур и игрового поля.

int is_game_over(const TetrisGameState* game) {
  // Проверка условия окончания игры
  // (например, если фигуры достигли верхней части игрового поля).
  return 0;  // Заглушка
}
/*
    5. Обработка фигур (CopyShape, DeleteShape, CheckPosition, GetNewShape,
   RotateShape): Эти функции управляют созданием, копированием, удалением и
   поворотом фигур. Они также проверяют, можно ли разместить фигуру на игровом
   поле.
    6. Очистка линий (Halleluyah_Baby): Функция проверяет, заполнены ли
   какие-либо линии на игровом поле, и если да, то очищает их и сдвигает все
   линии выше вниз.
    7. Отображение таблицы (PrintTable): Функция отвечает за отображение
   текущего состояния игрового поля и счета.
    8. Управление текущей фигурой (ManipulateCurrent): Функция обрабатывает
   действия пользователя, такие как движение фигуры влево, вправо, вниз и
   поворот.
*/

Shape CopyShape(Shape shape) {
  Shape new_shape = shape;
  char** copyshape = shape.array;
  new_shape.array = (char**)malloc(new_shape.width * sizeof(char*));
  int i, j;
  for (i = 0; i < new_shape.width; i++) {
    new_shape.array[i] = (char*)malloc(new_shape.width * sizeof(char));
    for (j = 0; j < new_shape.width; j++) {
      new_shape.array[i][j] = copyshape[i][j];
    }
  }
  return new_shape;
}

void DeleteShape(Shape shape) {
  int i;
  for (i = 0; i < shape.width; i++) {
    free(shape.array[i]);
  }
  free(shape.array);
}

int CheckPosition(Shape shape) {  // Check the position of the copied shape
  char** array = shape.array;
  int i, j;
  for (i = 0; i < shape.width; i++) {
    for (j = 0; j < shape.width; j++) {
      if ((shape.col + j < 0 || shape.col + j >= COLS ||
           shape.row + i >= ROWS)) {  // Out of borders
        if (array[i][j])              // but is it just a phantom?
          return FALSE;
      } else if (Table[shape.row + i][shape.col + j] && array[i][j])
        return FALSE;
    }
  }
  return TRUE;
}

void GetNewShape() {  // returns random shape
  Shape new_shape = CopyShape(ShapesArray[rand() % 7]);

  new_shape.col = rand() % (COLS - new_shape.width + 1);
  new_shape.row = 0;
  DeleteShape(current);
  current = new_shape;
  if (!CheckPosition(current)) {
    GameOn = FALSE;
  }
}

void RotateShape(Shape shape) {  // rotates clockwise
  Shape temp = CopyShape(shape);
  int i, j, k, width;
  width = shape.width;
  for (i = 0; i < width; i++) {
    for (j = 0, k = width - 1; j < width; j++, k--) {
      shape.array[i][j] = temp.array[k][i];
    }
  }
  DeleteShape(temp);
}

void WriteToTable() {
  int i, j;
  for (i = 0; i < current.width; i++) {
    for (j = 0; j < current.width; j++) {
      if (current.array[i][j])
        Table[current.row + i][current.col + j] = current.array[i][j];
    }
  }
}

void Halleluyah_Baby() {  // checks lines
  int i, j, sum, count = 0;
  for (i = 0; i < ROWS; i++) {
    sum = 0;
    for (j = 0; j < COLS; j++) {
      sum += Table[i][j];
    }
    if (sum == COLS) {
      count++;
      int l, k;
      for (k = i; k >= 1; k--)
        for (l = 0; l < COLS; l++) Table[k][l] = Table[k - 1][l];
      for (l = 0; l < COLS; l++) Table[k][l] = 0;
    }
  }
  timer -= 1000;
  score += 100 * count;
}

void PrintTable() {
  char Buffer[ROWS][COLS] = {0};
  int i, j;
  for (i = 0; i < current.width; i++) {
    for (j = 0; j < current.width; j++) {
      if (current.array[i][j])
        Buffer[current.row + i][current.col + j] = current.array[i][j];
    }
  }
  clear();
  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      printw("%c ", (Table[i][j] + Buffer[i][j]) ? 'O' : '.');
    }
    printw("\n");
  }
  printw("\nScore: %d\n", score);
}

void ManipulateCurrent(int action) {
  Shape temp = CopyShape(current);
  switch (action) {
    case 's':
      temp.row++;  // move down
      if (CheckPosition(temp))
        current.row++;
      else {
        WriteToTable();
        Halleluyah_Baby();  // check full lines, after putting it down
        GetNewShape();
      }
      break;
    case 'd':
      temp.col++;  // move right
      if (CheckPosition(temp)) current.col++;
      break;
    case 'a':
      temp.col--;  // move left
      if (CheckPosition(temp)) current.col--;
      break;
    case 'w':
      RotateShape(temp);  // yes
      if (CheckPosition(temp)) RotateShape(current);
      break;
  }
  DeleteShape(temp);
  PrintTable();
}

int main() {
  srand(time(0));
  score = 0;
  int c;
  initscr();
  struct timeval before, after;
  gettimeofday(&before, NULL);
  nodelay(stdscr, TRUE);
  GetNewShape();
  PrintTable();
  while (GameOn) {
    if ((c = getch()) != ERR) {
      ManipulateCurrent(c);
    }
    gettimeofday(&after, NULL);
    if (((double)after.tv_sec * 1000000 + (double)after.tv_usec) -
            ((double)before.tv_sec * 1000000 + (double)before.tv_usec) >
        timer) {  // time difference in microsec accuracy
      before = after;
      ManipulateCurrent('s');
    }
  }
  printw("\nGame over\n");
  DeleteShape(current);
  return 0;
}
