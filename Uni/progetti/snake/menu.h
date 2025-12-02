//
// Created by Matth on 27/03/2025.
//
#include <iostream>   // Per input/output standard
#include <fstream>    // Per la gestione dei file
#include <curses.h>   // Per gestire l'interfaccia utente con ncurses
#include <cstring>    // Per operazioni sulle stringhe
#include <ctime>      // Per generare numeri casuali basati sull'orario

using namespace std;

#ifndef MENU_H
#define MENU_H

const string CLASSIFICA_FILE = "classifica.txt"; // Nome del file che memorizza la classifica
const int MAX_CLASSIFICA = 5; // Numero massimo di voci nella classifica

class menu {
private:

    //attributi
    int evidenziato;  // Variabile per tracciare quale voce del menu è evidenziata
    const char * scelte[4] = { "Nuova Partita", "Visualizza Classifica", "Cancella Classifica", "Esci" }; // Voci del menu

    //metodi
public:
    menu();
    void mostraClassifica();
    void aggiornaClassifica(int nuovoPunteggio, const char* nome);
    void cancellaClassifica();
    int main_menu();
};

#endif //MENU_H