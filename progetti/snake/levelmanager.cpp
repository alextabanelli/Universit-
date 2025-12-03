//
// Created by Matth on 27/03/2025.
//
#include "levelmanager.h"

using namespace std;

void init(lista& l) {
    l.testa = NULL;
    l.coda = NULL;
}

void push(lista& l, int elem) {
    Nodo* p = new Nodo;
    p->elem = elem;
    p->next = NULL;
    p->prev = NULL;
    if (l.coda != NULL) {
        p->prev = l.coda;
        l.coda->next = p;
        l.coda = p;
    } else {
        l.testa = p;
        l.coda = p;
    }
}

void pop(lista& l) {
    if (l.testa == NULL) return; // Lista vuota, niente da fare

    Nodo* p = l.coda;
    if (l.testa == l.coda) {  // Caso in cui la lista ha un solo elemento
        l.testa = NULL;
        l.coda = NULL;
    } else {
        l.coda = p->prev;
        l.coda->next = NULL;
    }
    delete p;
}

void printList(const lista& l) {
    Nodo* current = l.testa;
    cout << "Lista livelli: ";
    while (current != NULL) {
        cout << current->elem << " ";
        current = current->next;
    }
    cout << endl;
}

levelmanager::levelmanager(int initialLevelDuration) : levelDuration(initialLevelDuration) {
    init(levels);
    push(levels, 1); // Livello iniziale
    currentLevel = levels.testa;
    levelStartTime = time(nullptr);
    statusMessage = "Benvenuto al livello 1!";
}

void levelmanager::updateLevel() {
    time_t currentTime = time(nullptr);
    int elapsedTime = static_cast<int>(currentTime - levelStartTime);

    if (elapsedTime >= levelDuration) {
        levelUp();
    }
}

void levelmanager::levelUp() {
    if (currentLevel->next == NULL) {
        // Aggiunge un nuovo livello se non esiste
        push(levels, currentLevel->elem + 1);
    }
    currentLevel = currentLevel->next;
    //levelStartTime = time(nullptr); // Reset del timer
    statusMessage = "Congratulazioni! Sei passato al livello " + to_string(currentLevel->elem) + "!";
}

void levelmanager::levelDown() {
    if (currentLevel == levels.testa) {
        statusMessage = "Sei gi\u00e0 al livello iniziale, non puoi tornare indietro!";
        return;
    }

    // Passa al livello precedente
    currentLevel = currentLevel->prev;
    //levelDuration = levelDuration -((levelDuration*MULT)-levelDuration) ; // Decremento la durata per il prossimo livello
    levelStartTime = time(nullptr); // Reset del timer
    statusMessage = "Sei tornato al livello " + to_string(currentLevel->elem) + "!";
}

void levelmanager::forceLevelUp() {
    levelUp();
}

double levelmanager::getSpeedMultiplier() const {
    return 1.0 + (currentLevel->elem - 1) * 0.1;
}

int levelmanager::getCurrentLevel() const {
    return currentLevel->elem;
}

int levelmanager::getLevelDuration() const {
    return levelDuration;
}

double levelmanager::getTimeRemaining() {
    time_t currentTime = time(nullptr);
    double elapsedTime = (currentTime - levelStartTime);
    return levelDuration - elapsedTime;
}

const string& levelmanager::getStatusMessage() const {
    return statusMessage;
}

const lista& levelmanager::getLevels() const {
    return levels;
}

void levelmanager::printLevels() const {
    printList(levels);
}