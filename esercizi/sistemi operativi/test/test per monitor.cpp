#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono> // Per sleep e random

using namespace std;

// Mutex globale solo per evitare che le stampe in console si sovrappongano
mutex print_mtx;

class MonitorNMeet {
private:
    static const int MAX_N = 100;

    // Strumenti C++ per simulare il comportamento del Monitor
    mutex monitor_mutex;             // Il "lucchetto" del monitor
    condition_variable waiters[MAX_N]; // Array di variabili condizione

    // Variabili di stato (come da pseudocodice concordato)
    int count[MAX_N];
    float sum[MAX_N];
    float average_results[MAX_N]; // Array per salvare i risultati separati

public:
    // Costruttore: Inizializzazione (init)
    MonitorNMeet() {
        for (int i = 0; i < MAX_N; i++) {
            count[i] = 0;
            sum[i] = 0.0;
            average_results[i] = 0.0;
        }
    }

    // La procedura entry
    float nmeet(unsigned int n, float val) {
        // Acquisizione del lock (entry point del monitor)
        unique_lock<mutex> lock(monitor_mutex);

        // Controllo validità n
        if (n <= 0 || n >= MAX_N) return -1.0;

        // Debug: Stampa ingresso
        {
            lock_guard<mutex> p(print_mtx);
            cout << "[Entrata] Thread ID " << this_thread::get_id() << " (gruppo n=" << n << ") valore=" << val << endl;
        }

        count[n]++;
        sum[n] += val;

        if (count[n] == n) {
            // --- ULTIMO PROCESSO ---
            
            // 1. Calcolo e salvataggio risultato
            average_results[n] = sum[n] / n;

            // Debug
            {
                lock_guard<mutex> p(print_mtx);
                cout << "--> [ULTIMO ARRIVATO] Gruppo n=" << n << " completo. Media calcolata: " << average_results[n] << ". RESET e SIGNAL." << endl;
            }

            // 2. RESET immediato (chiudiamo il turno)
            sum[n] = 0;
            count[n] = 0;

            // 3. Start CASCATA: sveglio il primo in coda
            waiters[n].notify_one(); 

            // Ritorno il risultato salvato
            return average_results[n];
        } 
        else {
            // --- PROCESSI IN ATTESA ---
            
            // Rilascio il lock e aspetto
            waiters[n].wait(lock);

            // APPENA SVEGLIATO (CASCATA):
            // Sveglio il prossimo thread in attesa prima di uscire
            waiters[n].notify_one();

            // Leggo il risultato salvato nell'array
            return average_results[n];
        }
        // Il lock viene rilasciato automaticamente all'uscita della funzione (scope exit)
    }
};

// Funzione worker per i thread
void thread_worker(MonitorNMeet& mon, int n, float val) {
    // Simulo un ritardo casuale per rendere l'ordine di arrivo imprevedibile
    this_thread::sleep_for(chrono::milliseconds(rand() % 200));

    float media = mon.nmeet(n, val);

    // Stampa risultato
    lock_guard<mutex> p(print_mtx);
    cout << "   [USCITA] Thread ID " << this_thread::get_id() << " (gruppo n=" << n << ") -> Media ricevuta: " << media << endl;
}

int main() {
    MonitorNMeet monitor;
    vector<thread> threads;

    cout << "=== TEST 1: Singolo gruppo n=3 (Valori: 10, 20, 30) ===" << endl;
    cout << "Aspettativa: Tutti escono insieme con media 20." << endl;
    
    threads.emplace_back(thread_worker, ref(monitor), 3, 10.0f);
    threads.emplace_back(thread_worker, ref(monitor), 3, 20.0f);
    threads.emplace_back(thread_worker, ref(monitor), 3, 30.0f);

    for (auto& t : threads) t.join();
    threads.clear();
    cout << "-------------------------------------------------------" << endl << endl;

    cout << "=== TEST 2: Concorrenza (Gruppo n=2 e Gruppo n=4 mescolati) ===" << endl;
    cout << "Gruppo A (n=2): 100, 200 -> Media attesa 150" << endl;
    cout << "Gruppo B (n=4): 5, 5, 5, 5 -> Media attesa 5" << endl;

    // Lancio i thread in ordine sparso
    threads.emplace_back(thread_worker, ref(monitor), 2, 100.0f); // A1
    threads.emplace_back(thread_worker, ref(monitor), 4, 5.0f);   // B1
    threads.emplace_back(thread_worker, ref(monitor), 4, 5.0f);   // B2
    threads.emplace_back(thread_worker, ref(monitor), 2, 200.0f); // A2 (Chiude A)
    threads.emplace_back(thread_worker, ref(monitor), 4, 5.0f);   // B3
    threads.emplace_back(thread_worker, ref(monitor), 4, 5.0f);   // B4 (Chiude B)

    for (auto& t : threads) t.join();

    cout << endl << "=== TEST COMPLETATO ===" << endl;

    return 0;
}