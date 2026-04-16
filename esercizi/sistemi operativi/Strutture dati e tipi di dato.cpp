Strutture dati e tipi di dato

TIPI DI DATI    
bool boleano{
    true/false;
}

int intero{
    numeri interi positivi e negativi;
    -3, 0, 42;
}

double reale{
    numeri con la virgola;
    3.14, -0.001, 2.0;
}

char carattere singolo{
    lettere, numeri, simboli;
    'A', 'b', '3', '#';
}

string stringa di caratteri{
    sequenza di caratteri;
    "Ciao", "123", "Hello, World!";
}

array vettore di elementi dello stesso tipo;{
    elementi accessibili tramite indice;
    int arr[5] = {1, 2, 3, 4, 5};
}

struct struttura di dati complessa{
    raccolta di variabili di diversi tipi;
    struct Punto {
        int x;
        int y;
    };
}

dynamic array vettore di dimensione variabile{
    array che può crescere o ridursi durante l esecuzione;
    vector<int> vec;
}

*p puntatore a un indirizzo di memoria{
    variabile che memorizza l indirizzo di un altra variabile;
    int a = 10;
    int* p = &a;
    per leggere il valore puntato: int valore = *p;
    per leggere l indirizzo: int indirizzo = p;
    p-> dereferenziazione del puntatore;
    esempio di dereferenziazione: struct Punto p = {3, 4};
    struct Punto* ptr = &p;
    int x = ptr->x; // x sarà 3
}

condition condizione{
    variabili usate nei monitor;
    condition cond;
    .wait(cond); // attende sulla condizione
    .signal(cond); // sveglia un thread in attesa sulla condizione
}

msg_t messaggio{
    struttura dati per la comunicazione tra processi;
    funzioni utili:
    msg.size(); // ritorna la dimensione del messaggio
    msg.chunk(size); // divide il messaggio in chunk di dimensione size, ritornando la lista di chunk
    msg.unite(); // unisce una lista di chunk in un unico messaggio
}

pid_t identificatore di processo{
    tipo di dato per rappresentare l ID di un processo;
    getpid(); // ottiene l ID del processo corrente
}


STRUTTURE DATI

Stack<elem> pila{
    collezione di elementi dello stesso tipo <elem>;
    new Stack<elem> = [];
    .push(elem); // aggiunge un elemento in cima alla pila
    .pop(); // rimuove e ritorna l elemento in cima alla pila
    .isEmpty(); // ritorna true se la pila è vuota
    .len(); // ritorna la lunghezza della pila
}

Queue<elem> coda{
    collezione di elementi dello stesso tipo <elem>;
    new Queue<elem> = [];
    .enqueue(elem); // aggiunge un elemento alla fine della coda
    .dequeue(); // rimuove e ritorna l elemento all inizio della coda
    .isEmpty(); // ritorna true se la coda è vuota
    .size(); // ritorna la lunghezza della coda, oppure .len();
    .remove(elem); // rimuove la prima occorrenza dell elemento specificato
}

List<elem> lista{
    collezione ordinata di elementi dello stesso tipo <elem>;
    new List<elem> = [];
    .append(elem); // aggiunge un elemento alla fine
    .remove(elem); // rimuove la prima occorrenza dell elemento
    .len(); // ritorna la lunghezza della lista
    .isEmpty(); // ritorna true se la lista è vuota
    .clear(); // rimuove tutti gli elementi dalla lista
    .get(index); // ritorna l elemento all indice specificato
    .removeAt(index); // rimuove l elemento all indice specificato
}

Map<key, value> mappa{
    collezione di coppie chiave-valore;
    new Map<key, value> = {};
    Map<pid_t, List <msg_t>> buffer; //mappa per la gestione dei messaggi
    .exists(chiave); // controlla se la chiave esiste nella mappa
    .keys(); // ritorna una lista di tutte le chiavi nella mappa
    .remove(chiave); // rimuove la coppia chiave-valore dalla mappa
    .clear(); // rimuove tutte le coppie chiave-valore dalla mappa
    .get(chiave); // ritorna il valore associato alla chiave
}



SEMAFORI

semaphore(int initial_value) semaforo{
    variabile di sincronizzazione intera;
    semaphore sem(initial_value);
    .P(); // decrementa il valore del semaforo, se è zero il processo si blocca
    .V(); // incrementa il valore del semaforo, sveglia un processo in attesa se presente
    semaphore mutex(1); // semaforo binario per mutua esclusione
}

MESSAGE PASSING

Invio di un messaggio{
    void asend(msg_t msg, pid_t dest); // invia un messaggio asincrono
    asend non blocca il processo mittente aspettanto che il messaggio venga ricevuto, 
    invece la ssend blocca il processo mittente fino a quando il messaggio non viene ricevuto.
}

Ricezione di un messaggio{
    msg_t arecv(pid_t sender); // riceve un messaggio asincrono
    arecv blocca il processo ricevente se non ci sono messaggi disponibili dal mittente specificato.
    per implementare una receive completamente asincrona che non blocca il processo ricevente se non ci sono messaggi disponibili,
    si può utilizzare una struttura dati per bufferizzare i messaggi in arrivo e restituire NULL se non ci sono messaggi disponibili.
    Quindi si usa o Map<pid_t, List <msg_t>> buffer, locale al processo ricevente, per memorizzare i messaggi in arrivo.
    Oppure un processo server dedicato che riceve tutti i messaggi e li memorizza in una struttura dati condivisa.
    server(){
        while (true){
            <sender, msg> = arecv(ANY);
            if (sender is in buffer.keys()) buffer[sender].append(msg);
            else {
                new List <msg_t> l = [];
                l.append(msg);
                buffer[sender] = l;
            }
        }
    }
}

MONITOR

monitor nome_monitor{
    struttura dati condivisa e procedure entry per la sincronizzazione dei processi;
    condition condizione; // variabile di condizione per la sincronizzazione
    procedure_entry nome_procedura(parametri){
        // corpo della procedura
        if (condizione_non_soddisfatta){
            condizione.wait(); // il processo si blocca sulla condizione
        }
        // operazioni sullo stato condiviso
        condizione.signal(); // sveglia un processo in attesa sulla condizione
    }
}

