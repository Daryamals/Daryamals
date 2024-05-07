#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include "defines.h"

TetFiguresT* createTetFiguresT(int count, int figures_size, TetBlock* figures_template);
void freeTetFiguresT(TetFiguresT* tetft);
TetField* createTetField(int width, int height);
void freeTetField(TetField* tetf);
TetGame* createTetGame(int field_width, int field_height, int figures_size, int count, TetBlock* figures_temlate);
void freeTetGame(TetGame* tetg);
void moveFigureDown(TetGame* tetg);
void moveFigureUp(TetGame* tetg);
void moveFigureRight(TetGame* tetg);
void moveFigureLeft(TetGame* tetg);
int collisionTet(TetGame* tetg);
void planFigure(TetGame* tetg);
int lineFilledTet(int i,TetField* tfl);
void dropLineTet(int i, TetField* tfl);
int eraseLinesTet(TetGame* tetg);
TetFigure* createTetFigure(TetGame* tetg);
void freeTetTetFigure(TetFigure* tf);
void dropNewFigure(TetGame* tetg);
TetFigure* rotTetFigure(TetGame* tetg);
void calculateTed(TetGame* tetg);