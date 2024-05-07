#ifndef DEFINES_H
#define DEFINES_H

#define TET_TICKS_START 30

//константы для возможных состояний игры
enum {
    TET_GAMEOVER = 0, 
    TET_PLAYING
};

//константы действий игрока
enum {
    TET_PLAYER_NOP = 0, // бездействие 
    TET_PLAYER_UP,
    TET_PLAYER_DOWN,
    TET_PLAYER_LEFT,
    TET_PLAYER_RIGHT
};

#endif