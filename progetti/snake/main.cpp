#include<iostream>
#include<curses.h>
#include<ctime>

//include delle classi
#include"snake.h"
#include"board.h"
#include"levelmanager.h"
#include"menu.h"

using namespace std;

int main() {
    int scelta_menu;
    bool quit=false;

    initscr();
    menu mi;

    while (!quit) {
        scelta_menu=mi.main_menu();

        switch (scelta_menu) {
            case 0: {
                char nome[20];
                int score=0,in_keyboard;
                const int ix=(getmaxx(stdscr)-getbegx(stdscr))-2,iy=(getmaxy(stdscr)-getbegy(stdscr))-6;
                bool valid_game=true;
                levelmanager lm(10);

                board b(iy, ix);
                nodelay(stdscr, TRUE); // Non blocca il programma in attesa dell'input
                clear();

                while (valid_game && lm.getTimeRemaining()>0)
                {
                    b.print_campo();

                    in_keyboard=getch();

                    if (in_keyboard == 'q') {
                        break;
                    } else if (in_keyboard == 'T') {
                        lm.forceLevelUp();
                    } else if (in_keyboard == 'P') {
                        lm.levelDown();
                    } else if (in_keyboard == ERR) {  //  Se nessun tasto è premuto...
                        in_keyboard = b.get_snake_facing();  //  Continua nella stessa direzione
                    }

                    valid_game=~b.move(in_keyboard);


                    //regola la velocità di movimento del serpente
                    napms(200/(lm.getSpeedMultiplier()));
                }

                endwin();
                clear();
                refresh();
                score=b.get_score();
                nodelay(stdscr, FALSE);

                mvprintw(2, 2, "Inserisci il tuo nome: ");  // Chiede il nome al giocatore

                echo();  // Abilita l'eco del nome inserito
                curs_set(1);  // Mostra il cursore
                getnstr(nome, 19);  // Ottiene il nome dell'utente
                noecho();  // Disabilita l'eco
                //curs_set(0);  // Nasconde il cursore

                mi.aggiornaClassifica(score, nome);

                nodelay(stdscr, FALSE); // Non blocca il programma in attesa dell'input
                b.~board();
            }
            break;

            case 1:
                mi.mostraClassifica();
            break;

            case 2:
                mi.cancellaClassifica();
            break;

            case 3:
                quit=true;
                break;
        }
    }

    return 0;
}