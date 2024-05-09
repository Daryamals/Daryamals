#include <check.h>

#include "s21_tetris.h"

// 1. CHECK
extern const Figure SamplesFigure[];
// extern void InputUser(int action, bool *GameOn, Figure *CurrentFigure, char
// Table[ROWS][COLS], int *score, int *Stop, int maxScore); extern void
// PrintTable(char Table[ROWS][COLS], int *score, Figure CurrentFigure, int
// maxScore);

START_TEST(check_rule_s_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleS(figure, table), 1);
}

START_TEST(check_rule_d_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleD(table, figure), 1);
}

START_TEST(check_rule_d_test_2) {
  char Table[ROWS][COLS] = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  Figure figure = {.row = 0,
                   .col = 0,
                   .width = 3,
                   .samples = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};

  ck_assert_int_eq(CheckRuleD(Table, figure), 0);
}

START_TEST(check_rule_a_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleA(table, figure), 1);
}

START_TEST(check_rule_w_test) {
  Figure figure = SamplesFigure[0];
  char table[ROWS][COLS] = {0};
  ck_assert_int_eq(CheckRuleW(table, figure), 1);
}

// 2.FILE
START_TEST(save_game_test) {
  int score = 200;
  int maxScore = 300;
  SaveGame(score, maxScore);
  int loaded_maxScore;
  LoadGame(&loaded_maxScore);
  ck_assert_int_eq(maxScore, loaded_maxScore);
}

START_TEST(load_game_test) {
  int score = 300;  // Исходное значение
  int loaded_score;
  LoadGame(&loaded_score);
  ck_assert_int_eq(score, loaded_score);
}

START_TEST(save_load_max_score_test) {
  int score = 300;
  int maxScore = 300;
  SaveGame(score, maxScore);
  int loaded_maxScore;
  LoadGame(&loaded_maxScore);
  ck_assert_int_eq(maxScore, loaded_maxScore);
}

START_TEST(save_load_game_test) {
  int score = 1500;
  int maxScore = 1500;
  SaveGame(score, maxScore);
  int loaded_score;
  LoadGame(&loaded_score);
  ck_assert_int_eq(score, loaded_score);
}

// 3.ADDITIONAL
START_TEST(level_test) {
  int score = 1200;
  ck_assert_int_eq(level(score), 200000);
}

START_TEST(Rotate_test) {
  Figure figure = SamplesFigure[0];
  Figure rotated_figure = Rotate(figure);
  // Check if the figure has been rotated correctly
  ck_assert_int_eq(rotated_figure.samples[0][1], figure.samples[1][0]);
  ck_assert_int_eq(rotated_figure.samples[1][0], figure.samples[0][1]);
}

START_TEST(DeleteString_test) {
  char table[ROWS][COLS] = {0};
  int score = 0;
  // Set up a table with a full row
  for (int i = 0; i < COLS; i++) {
    table[0][i] = 1;
  }
  DeleteString(table, &score);
  ck_assert_int_eq(score, 100);
  // Check if the row has been deleted
  for (int i = 0; i < COLS; i++) {
    ck_assert_int_eq(table[0][i], 0);
  }
}

// 4.InputUser

START_TEST(InputUser_test_1) {
  char Table[ROWS][COLS] = {0};
  Figure CurrentFigure = SamplesFigure[0];
  int score = 0;
  int Stop = 0;
  int maxScore = 0;
  bool GameOn = true;
  int action = 's';
  printf("\nstart\n");
  // CreateFigure(&CurrentFigure, Table, &GameOn);
  //   CurrentFigure.row = 0;
  //   CurrentFigure.col = 4;

  int end_row = CurrentFigure.row + 1;
  InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop, maxScore);
  printf("\nfinish\n");
  // Check if the figure has moved one cell to the right
  ck_assert_int_eq(CurrentFigure.row, end_row);
}

// START_TEST(InputUser_test_1) {
//   int action = 'd';
//   bool GameOn = true;
//   Figure CurrentFigure = SamplesFigure[0];
//   char Table[ROWS][COLS] = {0};
//   int score = 0;
//   int Stop = 0;
//   int maxScore = 0;
//   InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop, maxScore);
//   // Check if the figure has moved one cell to the right
//   ck_assert_int_eq(CurrentFigure.col, 1);
// }

/*

// START_TEST(InputUser_test_11) {
//     int action = ' ';
//     bool GameOn = true;
//     Figure CurrentFigure = SamplesFigure[0]; // Предполагается, что
SamplesFigure определен где-то в вашем коде
//     char Table[ROWS][COLS] = {0};
//     int score = 0;
//     int Stop = 0;
//     int maxScore = 0;
//     InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop,
maxScore);
//     ck_assert_msg(GameOn == false, "Game should be stopped after pressing
space");
// }

// START_TEST(InputUser_test_2) {
//   int action = 'w';
//   bool GameOn = true;
//   Figure CurrentFigure = SamplesFigure[0];
//   char Table[ROWS][COLS] = {0};
//   int score = 0;
//   int Stop = 0;
//   int maxScore = 0;
//   InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop, maxScore);
//   // Check if the figure has been rotated
//   ck_assert_int_eq(CurrentFigure.samples[0][1], 1);
//   ck_assert_int_eq(CurrentFigure.samples[1][0], 1);
// }

// START_TEST(InputUser_test_3) {
//   int action = 's';
//   bool GameOn = true;
//   Figure CurrentFigure = SamplesFigure[0];
//   char Table[ROWS][COLS] = {0};
//   int score = 0;
//   int Stop = 0;
//   int maxScore = 0;
//   // Set up a table with a full row
//   for (int i = 0; i < COLS; i++) {
//     Table[1][i] = 1;
//   }
//   InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop, maxScore);
//   // Check if the figure has moved down one cell
//   ck_assert_int_eq(CurrentFigure.row, 1);
//   // Check if the full row has been deleted
//   for (int i = 0; i < COLS; i++) {
//     ck_assert_int_eq(Table[1][i], 0);
//   }
//   // Check if the score has been updated
//   ck_assert_int_eq(score, 100);
// }

// START_TEST(InputUser_test_4) {
//   int action = 'o';
//   bool GameOn = true;
//   Figure CurrentFigure = SamplesFigure[0];
//   char Table[ROWS][COLS] = {0};
//   int score = 0;
//   int Stop = 0;
//   int maxScore = 0;
//   InputUser(action, &GameOn, &CurrentFigure, Table, &score, &Stop, maxScore);
//   // Check if the game has been stopped
//   ck_assert_int_eq(GameOn, false);
// }
*/
// 5.TABLE
/*
  START_TEST(PrintTable_test_1) {
  char Table[ROWS][COLS] = {0};
  int score = 0;
  Figure CurrentFigure = SamplesFigure[0];
  int maxScore = 0;

  // Set up the table with some values
  for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
      Table[i][j] = i + j;
      }
  }

  // Call the PrintTable function
  PrintTable(Table, &score, CurrentFigure, maxScore);

  // Check if the table has been printed correctly
  for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
      if (Table[i][j] + CurrentFigure.samples[i][j]) {
          ck_assert_int_eq(getch(), Table[i][j] + CurrentFigure.samples[i][j]);
      } else {
          ck_assert_int_eq(getch(), '.');
      }
      }
  }
  }

  START_TEST(PrintTable_test_2) {
  char Table[ROWS][COLS] = {0};
  int score = 100;
  Figure CurrentFigure = SamplesFigure[0];
  int maxScore = 200;

  // Set up the table with some values
  for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
      Table[i][j] = i + j;
      }
  }

  // Call the PrintTable function
  PrintTable(Table, &score, CurrentFigure, maxScore);

  // Check if the table has been printed correctly
  for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
      if (Table[i][j] + CurrentFigure.samples[i][j]) {
          ck_assert_int_eq(getch(), Table[i][j] + CurrentFigure.samples[i][j]);
      } else {
          ck_assert_int_eq(getch(), '.');
      }
      }
  }

  // Check if the additional information has been printed correctly
  ck_assert_int_eq(getch(), 'S');
  ck_assert_int_eq(getch(), 'c');
  ck_assert_int_eq(getch(), 'o');
  ck_assert_int_eq(getch(), 'r');
  ck_assert_int_eq(getch(), 'e');
  ck_assert_int_eq(getch(), ':');
  ck_assert_int_eq(getch(), ' ');
  ck_assert_int_eq(getch(), score);
  ck_assert_int_eq(getch(), 'M');
  ck_assert_int_eq(getch(), 'a');
  ck_assert_int_eq(getch(), 'x');
  ck_assert_int_eq(getch(), 'S');
  ck_assert_int_eq(getch(), 'c');
  ck_assert_int_eq(getch(), 'o');
  ck_assert_int_eq(getch(), 'r');
  ck_assert_int_eq(getch(), 'e');
  ck_assert_int_eq(getch(), ':');
  ck_assert_int_eq(getch(), ' ');
  ck_assert_int_eq(getch(), maxScore);
  }
*/
// 6.FIGURE
START_TEST(CreateFigure_test_1) {
  Figure CurrentFigure = {0};
  char Table[ROWS][COLS] = {0};
  bool GameOn = true;

  CreateFigure(&CurrentFigure, Table, &GameOn);

  ck_assert_int_ne(CurrentFigure.row, 0);
  ck_assert_int_ne(CurrentFigure.col, 4);
  ck_assert_int_eq(GameOn, true);
}

START_TEST(CreateFigure_test_2) {
  Figure CurrentFigure = {3};
  char Table[ROWS][COLS] = {0};
  bool GameOn = true;

  CreateFigure(&CurrentFigure, Table, &GameOn);
  ck_assert_int_ne(CurrentFigure.row, 0);
  ck_assert_int_ne(CurrentFigure.col, 4);
  //   ck_assert_int_eq(GameOn, false);
}

int main(void) {
  Suite *s1 = suite_create("tetris_check");
  TCase *tc1_1 = tcase_create("tetris_check");
  SRunner *sr = srunner_create(s1);

  Suite *s = suite_create("game_save_load");
  TCase *tc = tcase_create("game_save_load");

  int nf;

  suite_add_tcase(s1, tc1_1);
  // 1. CHECK
  tcase_add_test(tc1_1, check_rule_s_test);
  tcase_add_test(tc1_1, check_rule_d_test);
  tcase_add_test(tc1_1, check_rule_d_test_2);
  tcase_add_test(tc1_1, check_rule_a_test);
  tcase_add_test(tc1_1, check_rule_w_test);

  // 2.FILE
  // tcase_add_test(tc1_1, create_figure_test);
  tcase_add_test(tc1_1, save_game_test);
  tcase_add_test(tc1_1, load_game_test);
  tcase_add_test(tc1_1, save_load_max_score_test);
  tcase_add_test(tc1_1, save_load_game_test);

  // 3.ADDITIONAL
  tcase_add_test(tc1_1, level_test);
  tcase_add_test(tc1_1, Rotate_test);
  tcase_add_test(tc1_1, DeleteString_test);

  // 4.InputUser

  tcase_add_test(tc1_1, InputUser_test_1);
  //   tcase_add_test(tc1_1, InputUser_test_2);
  //   tcase_add_test(tc1_1, InputUser_test_3);
  //   tcase_add_test(tc1_1, InputUser_test_4);

  // 5.TABLE

  //   tcase_add_test(tc1_1, PrintTable_test_1);
  //   tcase_add_test(tc1_1, PrintTable_test_2);

  // 6.FIGURE

  tcase_add_test(tc1_1, CreateFigure_test_1);
  tcase_add_test(tc1_1, CreateFigure_test_2);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}

/*
Переделанные тесты под код:
    - 6.FIGURE

  tcase_add_test(tc1_1, CreateFigure_test_1);
  tcase_add_test(tc1_1, CreateFigure_test_2);


*/