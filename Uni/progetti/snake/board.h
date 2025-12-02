//
// Created by Matth on 27/03/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "snake.h"
#include <curses.h>
#include<iostream>

using namespace std;

//const int startx=getbegx(stdscr),starty=getmaxy(stdscr);
//const int ix=(getmaxx(stdscr)-getbegx(stdscr)),iy=(getmaxy(stdscr)-getbegy(stdscr));

class board {
private:

    //attributivv
    /*bool campo[height][width];
    int apple_x, apple_y;
    int score=0;
    int x_head=(height/2),y_head=(width/2+3);
    snake s=snake(&campo[height/2][width/2+1]);
    WINDOW *win= newwin(height+2, width+2, start_y, start_x);*/

    int height, width;
    bool **campo;
    int apple_x, apple_y;
    int score = 0;
    int x_head, y_head;
    snake s;
    WINDOW *win;

    //metodi
public:
    board(int h, int w);    // nuovo costruttore parametrico
    ~board();               // distruttore per liberare campo
    void spawn_apple();
    void print_campo();
    bool move(int m);
    int get_snake_facing();
    int get_score();
    void kill_win();
};

#endif //BOARD_H
