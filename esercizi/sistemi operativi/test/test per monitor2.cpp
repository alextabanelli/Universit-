#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <memory> // Per unique_ptr
#include <algorithm> // Per min_element

using namespace std;

// Mutex per la stampa pulita
mutex print_mtx;

class MinLenBB {
private:
    int N;          // Numero di buffer
    int NELEM;      // Capacità massima di ogni buffer
    int tot;        // Numero totale di elementi

    // Strutture dati
    vector<queue<int>> buffers;
    
    // Sincronizzazione
    mutex mtx;
    condition_variable ok2add;
    
    // Vettore di condition variables. 
    // Nota tecnica: le cond_var non sono copiabili, quindi usiamo unique_ptr per metterle nel vector.
    vector<unique_ptr<condition_variable>> ok2get;

    // Helper: Trova l'indice del buffer con meno elementi
    int minindex() {
        int min_idx = 0;
        size_t min_len = buffers[0].size();

        for (int i = 1; i < N; i++) {
            if (buffers[i].size() < min_len) {
                min_len = buffers[i].size();
                min_idx = i;
            }
        }
        return min_idx;
    }

public:
    // Costruttore
    MinLenBB(int num_buffers, int capacity_per_buffer) 
        : N(num_buffers), NELEM(capacity_per_buffer), tot(0) {
        
        buffers.resize(N);
        
        // Inizializziamo le condition variable per ogni buffer
        for(int i = 0; i < N; i++) {
            ok2get.push_back(make_unique<condition_variable>());
        }
    }

    // ENTRY: ADD
    void add(int obj) {
        unique_lock<mutex> lock(mtx);

        // 1. Controllo capacità totale
        // Uso while per sicurezza (anche se il monitor fosse Fair, protegge da spurious wakeups)
        while (tot >= N * NELEM) {
            {
                lock_guard<mutex> p(print_mtx);
                cout << "[ADD BLOCCATA] Sistema pieno (Tot: " << tot << "). Attendo..." << endl;
            }
            ok2add.wait(lock);
        }

        // 2. Scelgo il buffer migliore
        int n = minindex();

        // 3. Inserisco
        buffers[n].push(obj);
        tot++;

        {
            lock_guard<mutex> p(print_mtx);
            cout << " -> [ADD] Inserito " << obj << " nel buffer " << n 
                 << " (Len: " << buffers[n].size() << "/" << NELEM << ")" << endl;
        }

        // 4. Sveglio chi aspetta SU QUEL buffer specifico
        ok2get[n]->notify_one();
    }

    // ENTRY: GET
    int get(int bufnum) {
        unique_lock<mutex> lock(mtx);

        if (bufnum < 0 || bufnum >= N) return -1; // Controllo range

        // 1. Controllo disponibilità specifica
        while (buffers[bufnum].empty()) {
            {
                lock_guard<mutex> p(print_mtx);
                cout << "[GET BLOCCATA] Buffer " << bufnum << " vuoto. Attendo..." << endl;
            }
            ok2get[bufnum]->wait(lock);
        }

        // 2. Prelevo
        int obj = buffers[bufnum].front();
        buffers[bufnum].pop();
        tot--;

        {
            lock_guard<mutex> p(print_mtx);
            cout << " <- [GET] Prelevato " << obj << " dal buffer " << bufnum 
                 << ". (Posti liberi totali: " << (N*NELEM - tot) << ")" << endl;
        }

        // 3. Sveglio eventuali produttori in attesa
        ok2add.notify_one();

        return obj;
    }
};

// Funzione Produttore
void producer(MinLenBB& monitor, int id, int num_ops) {
    for (int i = 0; i < num_ops; i++) {
        int val = id * 100 + i; // Genero un valore unico
        monitor.add(val);
        this_thread::sleep_for(chrono::milliseconds(50)); // Simulo lavoro
    }
}

// Funzione Consumatore
void consumer(MinLenBB& monitor, int id, int target_buffer, int num_ops) {
    for (int i = 0; i < num_ops; i++) {
        int val = monitor.get(target_buffer);
        this_thread::sleep_for(chrono::milliseconds(80)); // Consumo un po' più lento
    }
}

int main() {
    // Configurazione: 3 Buffer, max 2 elementi ciascuno. Capacità tot = 6.
    int N_BUFFERS = 3;
    int CAPACITY = 2;
    MinLenBB monitor(N_BUFFERS, CAPACITY);

    vector<thread> threads;

    cout << "=== START SIMULAZIONE MINLENBB ===" << endl;
    cout << "Config: " << N_BUFFERS << " buffer di cap " << CAPACITY << " (Totale slot: " << N_BUFFERS*CAPACITY << ")" << endl;

    // Scenario:
    // 3 Produttori che cercano di riempire tutto velocemente.
    // 1 Consumatore lento che preleva SOLO dal buffer 0.
    // Risultato atteso: Il buffer 0 si svuota e riempie, gli altri si riempiono e restano pieni, 
    // costringendo i produttori a usare il buffer 0 o bloccarsi.

    // Avvio Produttori
    for(int i=0; i<3; i++) {
        threads.emplace_back(producer, ref(monitor), i+1, 3); // Ognuno produce 3 elementi
    }

    // Avvio Consumatore (si fissa sul buffer 0)
    threads.emplace_back(consumer, ref(monitor), 99, 0, 3); // Cerca di consumare 5 elementi dal buffer 0
    for (auto& t : threads) {
        t.join();
    }

    cout << "=== FINE SIMULAZIONE ===" << endl;
    return 0;
}