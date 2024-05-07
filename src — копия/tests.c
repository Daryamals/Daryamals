#include <check.h>
#include "s21_tetris.h"


// В файле s21_gui_tetris.c
extern const Figure SamplesFigure[];

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

START_TEST(create_figure_test) {
    char table[ROWS][COLS] = {0};
    bool game_on = TRUE;
    Figure current_figure;
    CreateFigure(&current_figure, table, &game_on);
    ck_assert_int_eq(current_figure.width, 5);
    // ck_assert_int_eq(current_figure.width, Figure.width);
}

int main(void) {
    Suite *s1 = suite_create("tetris");
    TCase *tc1_1 = tcase_create("tetris");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, check_rule_s_test);
    tcase_add_test(tc1_1, check_rule_d_test);
    tcase_add_test(tc1_1, check_rule_a_test);
    tcase_add_test(tc1_1, check_rule_w_test);
    tcase_add_test(tc1_1, create_figure_test);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0? 0 : 1;
}