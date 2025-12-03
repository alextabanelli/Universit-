//
// Created by Matth on 27/03/2025.
//
#include <iostream>
#include <ctime>
#include <curses.h>

using namespace std;

#ifndef GESTIONELIVELLI_H
#define GESTIONELIVELLI_H

struct Nodo {
    int elem;
    Nodo* next;
    Nodo* prev;
};

struct lista {
    Nodo* testa;
    Nodo* coda;
};

void init(lista& l);
void push(lista& l, int elem);
void pop(lista& l);
void printList(const lista& l);

class levelmanager {
private:
    lista levels;
    Nodo* currentLevel;
    double levelDuration; // Durata del livello in secondi
    time_t levelStartTime;
    string statusMessage; // Messaggio da visualizzare

public:
    levelmanager(int initialLevelDuration = 30);
    void updateLevel();
    void levelUp();
    void levelDown();
    void forceLevelUp();
    double getSpeedMultiplier() const;
    int getCurrentLevel() const;
    int getLevelDuration() const;
    double getTimeRemaining();
    const string& getStatusMessage() const;
    const lista& getLevels() const;
    void printLevels() const;
};

#endif //GESTIONELIVELLI_H
