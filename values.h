#ifndef VALUES_H
#define VALUES_H

const unsigned short SELL_SIZE = 100;
const unsigned short BOARD_SIZE = 4;
const unsigned short FRAMES_NUMBER = 3;
const unsigned short FPS = 60; // ПЛОХО - от FPS зависит скорость анимации

enum themeEnum
{
    girl_theme = 0,
    paper_theme = 1
};

const themeEnum THEME = paper_theme;

#endif // VALUES_H
