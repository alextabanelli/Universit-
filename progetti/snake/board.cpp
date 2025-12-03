//
// Created by Matth on 27/03/2025.
//
#include<iostream>
#include<ctime>
#include "board.h"

using namespace std;

board::board(int h, int w) : height(h), width(w), s(nullptr) {

    campo = new bool*[height];

    for (int c=0;c<height;c++)
    {
        campo[c]=new bool[width];

        for (int c2=0;c2<width;c2++)
        {
            campo[c][c2]=false;
        }
    }

    s = snake(&campo[0][0]);

    for (int c=-3;c<=3;c++)
    {
        s.push_back(&(campo[height/2][width/2+c]));
    }

    x_head = height/2;
    y_head = width/2+3;

    s.pop_front();
    spawn_apple();

    win = newwin(height+2,width+2,2,0);
}

board::~board()
{
    //fa crashare, da fixare!!!!
    for (int c=0;c<height;c++)
    {
        delete[] campo[c];
    }

    delete[] campo;
    delwin(win);
}

void board::spawn_apple() {
    do
    {
        apple_x = rand() % height;
        apple_y = rand() % width;
    } while (s.is_snake(&(campo[apple_x][apple_y]))); //  Assicura che la mela non appaia sul serpente
}

void board::print_campo() {
    refresh();

    box(win, 0, 0);

    for(int c=0; c<height; c++)
    {
        for(int c2=0; c2<width; c2++)
        {
            if(s.is_snake(&campo[c][c2]))
            {
                if(s.is_head(&(campo[c][c2])))
                {
                    mvwprintw(win, c+1, c2+1, "@");
                }
                else
                {
                    mvwprintw(win, c+1, c2+1, "#");
                }
            }
            else if(c==apple_x && c2==apple_y)
            { // Corretto l'errore con `&&`
                mvwprintw(win, c+1, c2+1, "O");
            }
            else
            {
                mvwprintw(win, c+1, c2+1," ");
            }
        }
    }

    mvwprintw(win, height+1, 2, "Score: %d", score);

    wrefresh(win);
    refresh();
}

bool board::move(int m) {
    /*
    direzioni di movimento:
    1: destra  D d
    2: sopra   W w
    3: sinistra A a
    4: sotto   S s
    */

    int f=s.get_facing();

    if ((m==65 || m==97) && s.get_facing()!=1)//A a
        f=3;
        else if ((m==68 || m==100) && s.get_facing()!=3) //D d
        f=1;
        else if ((m==83 || m==115) && s.get_facing()!=2) //S s
        f=4;
        else if ((m==87 || m==119) && s.get_facing()!=4) //W w
        f=2;

        int next_x = x_head, next_y = y_head;
        switch (f)
        {
            case 1: next_y += 1; break;  // Destra
            case 2: next_x -= 1; break;  // Sopra
            case 3: next_y -= 1; break;  // Sinistra
            case 4: next_x += 1; break;  // Sotto
        }

        //Se il serpente va oltre il bordo superiore (next_x < 0),
        //lo spostiamo in basso all'ultima riga (next_x = height - 1).
        if(next_x<0)
        {
            next_x=height-1;
        }

        //Se il serpente va oltre il bordo inferiore (next_x >= height),
        //lo riportiamo in cima (next_x = 0).
        else if(next_x>=height)
        {
            next_x=0;
        }

        //Se il serpente va oltre il bordo sinistro (next_y < 0),
        //lo portiamo all'ultima colonna a destra (next_y = width - 1).
        if(next_y<0)
        {
            next_y=width-1;
        }

        //Se il serpente va oltre il bordo destro (next_y >= width),
        //lo riportiamo nella prima colonna (next_y = 0).
        else if(next_y>=width)
        {
            next_y=0;
        }

        //  Controllo collisione con il corpo
        if (s.is_snake(&(campo[next_x][next_y])))
        {
            endwin();
            cout<<"Game Over! Hai colpito te stesso!"<<endl;
            cout<<"Punteggio finale: "<<score<<endl;
            return false;
        }

        //  Controllo se ha mangiato la mela
        if (next_x == apple_x && next_y == apple_y)
        {
            score=score+100;  //  Incrementa il punteggio
            spawn_apple();  //  Genera una nuova mela
        }

    s.pop_front();

    s.push_back(&(campo[next_x][next_y]));  //  Muove la testa
    x_head = next_x;
    y_head = next_y;
    s.change_facing(f);
    return true;
}

int board::get_snake_facing()
{
    return s.get_facing();
}

int board::get_score()
{
    return score;
}