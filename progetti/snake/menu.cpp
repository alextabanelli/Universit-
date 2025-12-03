//
// Created by Matth on 27/03/2025.
//
#include "menu.h"

using namespace std;

menu::menu() : evidenziato(0) {}

void menu::mostraClassifica() {
    ifstream file(CLASSIFICA_FILE);  // Apre il file della classifica in lettura
    clear();  // Pulisce lo schermo
    mvprintw(2, 2, "Classifica:");  // Stampa il titolo della classifica
    int y = 4;  // Variabile per gestire la posizione verticale per stampare le voci della classifica

    if (file.is_open()) {  // Verifica che il file sia stato aperto correttamente
        int punteggio;
        char nome[20];
        int i = 1;
        // Legge il contenuto del file riga per riga (nome e punteggio)
        while (file >> nome >> punteggio) {
            mvprintw(y++, 4, "%d) %s - %d", i++, nome, punteggio);  // Stampa la classifica formattata
        }
        file.close();  // Chiude il file dopo averlo letto
    }

    mvprintw(y + 2, 2, "Premi un tasto per tornare al menu...");  // Messaggio per l'utente
    refresh();  // Aggiorna lo schermo per visualizzare il contenuto
    getch();  // Attende che l'utente prema un tasto
}

void menu::aggiornaClassifica(int nuovoPunteggio, const char* nome) {
    ifstream file(CLASSIFICA_FILE);  // Apre il file della classifica in lettura
    int punteggi[MAX_CLASSIFICA + 1] = {0};  // Array per memorizzare i punteggi, uno in più per aggiungere un nuovo punteggio
    char nomi[MAX_CLASSIFICA + 1][20] = {{0}};  // Array per memorizzare i nomi, uno in più per il nuovo nome
    int count = 0;

    // Se il file è aperto, legge i punteggi e i nomi dalla classifica
    if (file.is_open()) {
        while (file >> nomi[count] >> punteggi[count]) {
            count++;  // Conta le righe lette
        }
        file.close();  // Chiude il file dopo aver letto il contenuto
    }

    // Aggiunge il nuovo punteggio e nome alla lista
    punteggi[count] = nuovoPunteggio;
    strncpy(nomi[count], nome, 19);  // Copia il nome nella lista
    count++;

    // Ordinamento dei punteggi in ordine decrescente (dal più alto al più basso)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (punteggi[j] > punteggi[i]) {  // Se il punteggio di j è maggiore di i, scambia
                // Scambio dei punteggi
                int temp = punteggi[i];
                punteggi[i] = punteggi[j];
                punteggi[j] = temp;

                // Scambio dei nomi
                char tempNome[20];
                strcpy(tempNome, nomi[i]);
                strcpy(nomi[i], nomi[j]);
                strcpy(nomi[j], tempNome);
            }
        }
    }

    // Scrive la classifica aggiornata nel file
    ofstream outFile(CLASSIFICA_FILE);
    for (int i = 0; i < min(count, MAX_CLASSIFICA); i++) {  // Scrive massimo MAX_CLASSIFICA voci
        outFile << nomi[i] << " " << punteggi[i] << endl;
    }
    outFile.close();  // Chiude il file dopo aver scritto i nuovi dati
}

void menu::cancellaClassifica() {
    ofstream outFile(CLASSIFICA_FILE, ios::trunc);  // Apre il file in modalità "trunc" per cancellarne il contenuto
    outFile.close();  // Chiude il file dopo averlo svuotato
}

int menu::main_menu() {
    int scelta;
    initscr();  // Inizializza la finestra ncurses
    noecho();  // Disabilita l'eco dei caratteri digitati
    curs_set(0);  // Nasconde il cursore
    keypad(stdscr, TRUE);  // Abilita i tasti funzione e le frecce

    // Ciclo principale per gestire la navigazione del menu
    while (true) {
        clear();  // Pulisce lo schermo
        mvprintw(2, 2, "Menu");  // Stampa il titolo del menu

        // Stampa le voci del menu, evidenziando quella selezionata
        for (int i = 0; i < 4; i++) {
            if (i == evidenziato) attron(A_REVERSE);  // Evidenzia la voce selezionata
            mvprintw(4 + i, 4, "%s", scelte[i]);  // Stampa la voce del menu
            if (i == evidenziato) attroff(A_REVERSE);  // Rimuove l'evidenziazione
        }
        refresh();  // Aggiorna lo schermo per visualizzare le modifiche

        scelta = getch();  // Ottiene la scelta dell'utente

        // Gestione delle frecce su e giù per spostarsi tra le voci
        switch (scelta) {
            case KEY_UP:
                evidenziato = (evidenziato == 0) ? 3 : evidenziato - 1;  // Muove la selezione verso l'alto
                break;
            case KEY_DOWN:
                evidenziato = (evidenziato == 3) ? 0 : evidenziato + 1;  // Muove la selezione verso il basso
                break;
            case 10:  // Se viene premuto INVIO
                return evidenziato;
            }
        }
    endwin();  // Chiude ncurses e termina l'applicazione
}