//Esercitazione sistemi operativi
/*
esame 21/07/2025
Scrivere il monitor nmeet che ha una funzione di interfaccia:
float nmeet(unsigned int n, float val)
La funzione nmeet blocca il processo chiamante fino a quando n processi abbiano richiamato nmeet con parametro n.
(es due processi che hanno chiamato la nmeet con n=3 rimangono bloccati, quando un terzo processo chiama nmeet
con n=3, i tre processi continuano l'esecuzione.) Il valore di ritorno di nmeet e' la media dei valori 'val' passati dagli n
processi che hanno sbloccato la chiamata nmeet.
*/

// Creao un array di condizioni, una per ogni possibile valore di n
monitor nmeet {
    const int MAX_N = 100; // Definire un limite massimo per n
    condition waiters[MAX_N]; // Condizioni per ogni n
    int count[MAX_N]; // Numero di processi arrivati per ogni n
    float sum[MAX_N]; // Somma dei valori per ogni n
    float average[MAX_N]; // Necessario: un risultato per ogni n
}

// Inizializzazione delle strutture dati, viene eseguita una volta al momento della creazione del monitor
    init {
        for (int i = 0; i < MAX_N; i++) {
            count[i] = 0;
            sum[i] = 0.0;
            average[i] = 0.0;
        }
    }

    procedure_entry float nmeet(unsigned int n, float val) {
        if (n <= 0 || n >= MAX_N) return -1.0; // Gestione errore per n non valido

        count[n]++; // Incrementa il conteggio per il gruppo n
        sum[n] += val; // Aggiunge il valore al totale per il gruppo n

        if (count[n] == n) {
            // L'ultimo processo arrivato:
            average[n] = sum[n] / n; // Salva il risultato
            
            // RESET immediato dello stato per il prossimo gruppo
            sum[n] = 0;
            count[n] = 0;

            // Inizia la cascata di risvegli
            waiters[n].signal(); 
            
            return average[n];
        } 
        else {
            // I processi che arrivano prima restano in attesa:
            waiters[n].wait();

            // Cascata: chi si sveglia sveglia il prossimo
            waiters[n].signal();

            // Tutti leggono il valore che era stato "congelato" dall'ultimo
            return average[n];
        }
}



/*
esame 23/06/2025
 Scrivere il monitor minlenbb che fornisce le seguenti procedure entry:
void minlenbb.add(objtype obj)
objtype minlenbb.get(int bufnum)
Il monitor gestisce N buffer ognuno dei quali contiene NELEM elementi.
La funzione add inserisce obj come elemento nel buffer che contiene meno elementi. In caso più buffer abbiano lo
stesso numero minimo di elementi viene scelto il buffer di indice minore.
La funzione get prende un elemento dal buffer di indice bufnum
*/


monitor minlenbb {
    // Strutture dati
    queue buffer[N];      // N code (assumiamo gestiscano loro la memoria interna)
    int tot = 0;              // Numero totale di elementi nel sistema
    const int NELEM = ...; // Capacità massima di UN buffer

    // Condition variables
    condition ok2add;     // Attesa se TUTTO il sistema è pieno (tot == N*NELEM)
    condition ok2get[N];  // Attesa specifica se il buffer[bufnum] è vuoto

    // Funzione helper privata
    int minindex(buffer) {
        int min_idx = 0;
        // Cerca l'indice del buffer con meno elementi
        for (int i = 1; i < N; i++) {
            // Nota: < stretto garantisce che a parità di lunghezza vinca l'indice minore
            if (buffer[i].len() < buffer[min_idx].len()) {
                min_idx = i;
            }
        }
        return min_idx;
    }
}

    procedure entry void add(objtype obj) {
        // 1. Controllo Capacità Globale
        // Usiamo WHILE per robustezza (Mesa semantics)
        while (tot >= N * NELEM) {
            ok2add.wait();
        }

        // 2. Scelta del buffer
        // MATEMATICA: Se tot < N*NELEM, allora esiste almeno un buffer con len < NELEM.
        // Poiché minindex restituisce quello con len minima, esso avrà sicuramente spazio.
        int n = minindex(buffer);

        // 3. Inserimento
        buffer[n].enqueue(obj);
        tot++;

        // 4. Signal specifica
        // Ho inserito in 'n', quindi sveglio solo chi aspetta su 'n'
        ok2get[n].signal();
    }

    procedure entry objtype get(int bufnum) {
        // 1. Controllo disponibilità specifica
        // Qui devo controllare SOLO il buffer richiesto 'bufnum'
        while (buffer[bufnum].len() == 0) {
            ok2get[bufnum].wait();
        }

        // 2. Rimozione
        objtype obj = buffer[bufnum].dequeue();
        tot--;

        // 3. Signal globale
        // Ho liberato un posto nel sistema, sveglio chi voleva aggiungere
        ok2add.signal();

        return obj;
    }


/*
esame 23/01/2025 es1
Il monitor count bounded buffer (cbb) gestisce un buffer limitato di MAX elementi.
cbb ha due procedure entry:
void write(obj_t el)
int remove(obj_t el)
La funzione write inserisce un elemento nel buffer. Se vi sono già MAX elementi i processi che chiamano la funzione
write devono attendere in ordine FIFO.
La funzione remove deve eliminare dal buffer tutti gli elementi di valore uguale al parametro el presenti nel buffer al
momento della chiamata. Il valore di ritorno rappresenta il numero di elementi cancellati dal buffer. Se non vi sono
elementi restituisce zero.
*/

monitor cbb{
    int MAX = 100;
    list buffer;
    int elem = 0;
    condition ok2write;
    //condition ok2remove; non necessaria in questo caso se nel caso vuoto vogliamo che ritorni 0 direttamente, altrimenti si potrebbe usare per far attendere in caso di buffer vuoto
    buffer.remove(obj_t el); //funzione di lista che elimina el e ritorna true se ha rimosso l'elemento, altrimenti false
}


procedur_entry void write (obj_t el){
    if (elem >= MAX){
        ok2write.wait();
    }
    buffer.insert(el);
    elem++;
}

procedur_entry int remove (obj_t el){
    int i = 0; //Cotatore per le occorrenze di el nel buffer
    while (buffer.remove(el)){
        elem--;
        i++;
    }
    if (i > 0){
        for (int j = 0; j < i; j++){
            ok2write.signal();
        }
    }
    return i;
}




/*15/01/2020
Il monitor "semaforo con timeout" semtimeout deve fornire tre procedure entry:
void V(void)
boolean P(unsigned int timeout)
void tick(void)
Vale l'invariante dei semafori generali. La funzione tick viene richiamata ad ogni millisecondo. Un processo messo in
attesa a causa di una P attende al massimo il numero di millisecondi indicato nel parametro.
Se un processo viene riattivato per timeout la P ritorna valore vero, altrimenti falso. Le operazioni V devono riattivare i
processi in attesa in ordine FIFO.
Scrivere semtimeout.
*/

monitor semtimeout {
    int S = 0; // Valore del semaforo (inizializzato a piacere, es. 0)

    // Struttura per ogni processo in attesa
    struct Process {
        int timeLeft;      // Millisecondi rimanenti
        bool expired;   // Flag: true se svegliato da tick, false se da V
        condition cond;    // Condizione privata per dormire
    };

    // Lista gestita come coda (FIFO) ma scansionabile
    // Usiamo una lista doppiamente linkata per rimuovere nodi in mezzo facilmente
    List<Process*> queue; 

    // --- PROCEDURE ENTRY ---

    procedure_entry bool P(unsigned int timeout) {
        // CASO 1: Semaforo Verde -> Prendo e vado
        if (S > 0) {
            S--;
            return false; // False = Nessun timeout
        }

        // CASO 2: Semaforo Rosso -> Mi metto in coda
        Process myProc;
        myProc.timeLeft = timeout;
        myProc.expired = false; // Presuppongo andrà tutto bene
        
        // Inserimento in coda (FIFO)
        queue.push_back(&myProc);

        // Mi addormento sulla MIA condizione privata
        myProc.cond.wait();

        // --- RISVEGLIO ---
        // Qui arrivo se V() o tick() mi hanno fatto la signal
        
        if (myProc.expired == true) {
            // Sono stato svegliato dalla tick() per timeout
            return true; 
        } else {
            // Sono stato svegliato dalla V()
            // NOTA: Non faccio S-- perché la V non ha fatto S++.
            // La risorsa mi è stata "passata" direttamente.
            return false;
        }
    }

    procedure entry void V(void) {
        if (queue.isEmpty()) {
            // Nessuno aspetta: incremento il contatore (Semaforo Verde)
            S++;
        } else {
            // Qualcuno aspetta: NON incremento S.
            // Sveglio il primo della lista (FIFO) e gli passo la risorsa.
            Process* head = queue.pop_front();
            
            head->expired = false; // Segnalo che ha ottenuto la risorsa
            head->cond.signal();   // Sveglio quel processo specifico
        }
    }

    procedure entry void tick(void) {
        // Scansiono tutta la lista per aggiornare i timer
        Iterator it = queue.head();
        
        while (it != queue.tail()) {
            Process* proc = *it;
            proc->timeLeft--;

            if (proc->timeLeft <= 0) {
                // IL TEMPO È SCADUTO PER QUESTO PROCESSO
                
                // 1. Lo rimuovo dalla lista di attesa
                it = queue.remove(it); 
                
                // 2. Imposto il flag di timeout
                proc->expired = true;
                
                // 3. Lo sveglio forzatamente
                proc->cond.signal();
            } else {
                it++; // Passo al prossimo
            }
        }
    }
}


/*
Per poter partire un passeggero di uno specifico volo esegue i passi seguenti:
fila = volo.checkin() // al check-in viene attribuito il posto (il numero della fila va da 1 a 20,
 // 5 posti per fila), se i posti sono esauriti si attende per fare checkin
 // sul prossimo volo
… va al gate
volo.imbarco(fila) // il passeggero si può imbarcare quando consentito dal personale di terra
… sali sull’aereo
volo.a_bordo() // il passeggero è a bordo.
Mentre il personale di terra quando l’aereo è al gate, volendo imbarcare i passeggeri dal fondo esegue il seguente
codice:
for (i = 20; i > 0; i--)
 volo.chiama(i) //tutti i passeggeri delle file >= i possono imbarcarsi
 … attendi
volo.imbarco_completo() // la funzione attende il completamento dell’imbarco: l’aereo puo’
 partire solo quando tutti i passeggeri passati al checkin sono a bordo
Scrivere il monitor volo
*/

<>

monitor volo {
    const int MAXPASS = 100;
    const int POSTI_PER_FILA = 5;
    
    int countcheckin;
    int current_called_fila; // La fila attualmente chiamata dal personale
    int onboard;
    
    condition ok2checkin;
    condition ok2leave;
    condition ok2imbarco[20]; // Una condizione per ogni fila (0..19 rappresentano 1..20)

    // Init
    init {
        countcheckin = 0;
        onboard = 0;
        current_called_fila = 21; // Inizialmente nessuna fila (21 > 20) può salire
    }

    procedure entry int checkin() {
        // Attesa se il volo è pieno
        while (countcheckin >= MAXPASS) {
            ok2checkin.wait();
        }
        
        countcheckin++;
        int fila = (countcheckin - 1) / POSTI_PER_FILA + 1;
        return fila;
    }

    procedure entry void imbarco(int fila) {
        // I passeggeri devono aspettare finché la loro fila non viene chiamata.
        // La chiamata va all'indietro (20, 19, ...).
        // Se io sono fila 5, devo aspettare che current scenda a 5.
        // Se current è 20, 5 < 20 -> VERO (aspetto).
        while (fila < current_called_fila) {
            ok2imbarco[fila-1].wait();
        }
        
        // Nota: Qui non serve fare signal() a cascata.
        // È la funzione chiama() del personale che deve svegliare la fila.
    }

    procedure entry void a_bordo() {
        onboard++;
        // Se sono l'ultimo passeggero atteso, dico all'aereo che può partire
        if (onboard == MAXPASS) {
            // Nota: la traccia non specifica se l'aereo parte pieno o 
            // solo con chi ha fatto checkin. Assumiamo la seconda (più generica).
             ok2leave.signal();
        }
    }

    // --- FUNZIONI PERSONALE DI TERRA ---

    procedure entry void chiama(int fila) {
        current_called_fila = fila;
        
        // Sveglio TUTTI i passeggeri di questa specifica fila
        // Usiamo signal_all (broadcast) perché ci sono fino a 5 persone
        ok2imbarco[fila-1].signal_all();
    }

    procedure entry void imbarco_completo() {
        // Attende che tutti i passeggeri che hanno fatto checkin siano a bordo
        while (onboard < countcheckin) {
            ok2leave.wait();
        }
        
        // Reset per il prossimo volo
        onboard = 0;
        countcheckin = 0;
        current_called_fila = 21; // Resetta lo stato imbarco
        
        // Sveglio TUTTI quelli che aspettavano il checkin per il nuovo volo
        ok2checkin.signal_all();
    }
}


/*
Un servizio chiamato threshlocking ha le due seguenti funzioni di interfaccia:
void threshlock(int level)
void chthreshold(int newlevel)
Il servizio mantiene il valore di soglia corrente: un numero intero, con valore iniziale zero.
Se un processo chiama threshlock con parametro level maggiore o uguale alla soglia corrente viene bloccato,
altrimenti no.
La funzione chthreshold cambia il valore di soglia portandolo a newlevel. Tutti i processi in attesa che avevano
specificato un parametro level minore di newlevel devono essere sbloccati.
Implementare il servizio utilizzando semafori.
*/

<>

/* Strutture Dati */
#define MAX_LEVEL 100 // Assumiamo un massimo ragionevole

semaphore mutex(1);
semaphore tlock[MAX_LEVEL](0); // Inizializzati tutti a 0 (rossi)
int plock[MAX_LEVEL];          // Contatori processi bloccati (init a 0)
int currlevel = 0;

void threshlock(int level) {
    mutex.P();
    
    // Controllo la condizione
    if (level >= currlevel) {
        // MI BLOCCO
        plock[level]++;
        mutex.V();         // Rilascio il mutex PRIMA di bloccarmi
        tlock[level].P();  // Mi addormento sul semaforo privato
        
        // AL RISVEGLIO:
        // Qui arrivo solo quando chthreshold mi ha sbloccato.
        // Non devo fare altro (niente check, niente V su mutex).
        // Sono libero di andare.
    } else {
        // PASSO SUBITO
        mutex.V();
    }
}

void chthreshold(int newlevel) {
    int i;
    mutex.P();
    
    currlevel = newlevel;
    
    // Devo sbloccare TUTTI i processi che aspettavano un livello < newlevel.
    // Scorro tutti i livelli inferiori alla nuova soglia.
    for (i = 0; i < newlevel; i++) {
        
        // Svuoto la coda di quel livello specifico
        while (plock[i] > 0) {
            plock[i]--;      // Decremento il contatore dei bloccati
            tlock[i].V();    // Sveglio un processo
        }
    }
    
    mutex.V();
}


/*
 Un servizio di message passing asincrono limitato consente di spedire messaggi che contengono un
indentificativo di processo, una flag booleana e un corpo del messaggio di lunghezza <= 1500 byte.
lsend(<pid, flag, body>, dest) // spedisce un messaggio a dest; len(body) <= 1500
<pid, flag, body> = lrecv(sender) // riceve (FIFO) un messaggio da sender (può essere ANY).
Scrivere un servizio di message passing asincrono standard facendo uso di lsend, lrecv.
*/


// --- SENDER ---
void asend(msg_t msg, pid_t dst) {
    bool f = false;
    int last_size = 0;
    
    // Immaginiamo che msg.split restituisca una coda di chunk
    Queue<chunk> q = msg.split(1500);
    
    // CORREZIONE 1: while (!q.isEmpty())
    while (!q.isEmpty()) {
        chunk c = q.dequeue();
        
        // Se il chunk è più piccolo del massimo, è sicuramente l'ultimo
        if (c.size() < 1500) {
            f = true;
        } else {
            f = false; // Importante resettarlo se fosse rimasto sporco
        }
        
        lsend(<getpid(), f, c>, dst);
        
        last_size = c.size();
    }
    
    // GESTIONE EDGE CASE (Multipli di 1500)
    // Se l'ultimo pacchetto inviato era "pieno" (1500), la flag era false.
    // Dobbiamo mandare un pacchetto vuoto con flag=true per dire "FINE".
    if (last_size == 1500) {
        lsend(<getpid(), true, NULL>, dst);
    }
}

// --- RECEIVER ---
msg_t areceive(pid_t snd) {
    msg_t msg = ""; // Inizializzo vuoto
    bool flag = false;
    
    while (!flag) {
        // Assumiamo che lrecv filtri per 'snd' come da tua logica
        <sender, f, body> = lrecv(snd);
        
        flag = f;
        
        // Se body è NULL (caso pacchetto vuoto finale), non aggiungo nulla
        if (body != NULL) {
            msg = msg + body;
        }
    }
    
    return msg;
}

//con gestione del database per memorizzare i messaggi ricevuti ma non ancora letti

// --- STRUTTURE DATI ---

// Struttura per tenere traccia dello stato di un messaggio parziale
struct MessageBuffer {
    msg_t content = ""; // Il corpo del messaggio ricostruito finora
    bool is_complete = false; // Flag che diventa true quando arriva l'ultimo pezzo
};

// Il nostro "Database" locale: Mappa da PID Mittente -> Buffer
// In un esercizio d'esame puoi trattarlo come un oggetto astratto 'db'
// db.get(pid), db.add(pid, chunk, flag), ecc.
Map<pid_t, MessageBuffer> db; 

// --- SENDER ---
// (La logica Sender rimane invariata perché era corretta e robusta)
void asend(msg_t msg, pid_t dst) {
    bool f = false;
    int last_size = 0;
    
    // Divide il messaggio in pezzi da 1500
    Queue<chunk> q = msg.split(1500);
    
    while (!q.isEmpty()) {
        chunk c = q.dequeue();
        
        // Se il chunk è < 1500, è l'ultimo "reale".
        if (c.size() < 1500) {
            f = true;
        } else {
            f = false;
        }
        
        lsend(<getpid(), f, c>, dst);
        last_size = c.size();
    }
    
    // ZLP Strategy: Se l'ultimo era esattamente 1500, mandiamo un pacchetto vuoto finale
    if (last_size == 1500) {
        lsend(<getpid(), true, NULL>, dst);
    }
}

// --- RECEIVER ---
msg_t arecv(pid_t target_sender) {
    
    // 1. FAST PATH: Controllo se il messaggio è già completo nel DB
    // (Magari è stato ricevuto interamente mentre aspettavo un altro processo prima)
    if (db.exists(target_sender) && db[target_sender].is_complete) {
        msg_t completed_msg = db[target_sender].content;
        
        // Pulizia: Rimuovo il messaggio consegnato dal DB per liberare memoria
        // e prepararmi a riceverne uno nuovo in futuro dallo stesso mittente
        db.remove(target_sender); 
        
        return completed_msg;
    }
    
    // 2. SLOW PATH: Devo ricevere dalla rete
    while (true) {
        // Uso ANY per scaricare la rete e non bloccare altri flussi.
        // Leggo qualsiasi cosa arrivi.
        <pid_mittente, is_last, chunk> = lrecv(ANY);
        
        // Aggiungo il pezzo al buffer del mittente corrispondente
        // Se la voce non esiste nel DB, la crea automaticamente
        if (chunk != NULL) {
            db[pid_mittente].content = db[pid_mittente].content + chunk;
        }
        
        // Se il flag è true, segno che per QUEL mittente il messaggio è finito
        if (is_last) {
            db[pid_mittente].is_complete = true;
        }
        
        // 3. CHECK: Ho finito di assemblare il messaggio del mittente richiesto?
        // Nota: Controllo 'target_sender', non necessariamente 'pid_mittente' appena ricevuto
        if (db[target_sender].is_complete) {
            msg_t completed_msg = db[target_sender].content;
            db.remove(target_sender); // Reset
            return completed_msg;
        }
    }
}

/*
/ ASSUNZIONI SULL'OGGETTO 'db':
   Immaginiamo che ci venga fornito un oggetto globale 'db' con questa interfaccia:
   
   - db.append(pid, chunk): Aggiunge un pezzo al buffer del processo 'pid'.
   - db.set_complete(pid): Segna che il messaggio di 'pid' è finito.
   - db.is_ready(pid): Ritorna true se abbiamo un messaggio completo da 'pid'.
   - db.extract(pid): Ritorna il messaggio completo e pulisce il buffer.
/

// --- SENDER ---
// (Identico a prima: la logica di invio non dipende dal DB del ricevente)
void asend(msg_t msg, pid_t dst) {
    bool f = false;
    int last_size = 0;
    
    Queue<chunk> q = msg.split(1500);
    
    while (!q.isEmpty()) {
        chunk c = q.dequeue();
        
        // Logica per capire se è l'ultimo pezzo
        if (c.size() < 1500) {
            f = true;
        } else {
            f = false;
        }
        
        lsend(<getpid(), f, c>, dst);
        last_size = c.size();
    }
    
    // ZLP: Se l'ultimo era pieno, ne mandiamo uno vuoto per chiudere
    if (last_size == 1500) {
        lsend(<getpid(), true, NULL>, dst);
    }
}

// --- RECEIVER ---
msg_t arecv(pid_t target_sender) {
    
    // 1. FAST PATH: Controllo se il DB ha già il messaggio pronto
    // (Magari è arrivato mentre facevo altro)
    if (db.is_ready(target_sender)) {
        return db.extract(target_sender);
    }
    
    // 2. SLOW PATH: Ricezione dalla rete
    while (true) {
        // Ricevo da CHIUNQUE (ANY) per non bloccare il sistema
        <pid_mittente, is_last, chunk> = lrecv(ANY);
        
        // 3. BUFFERIZZAZIONE: Delega tutto al DB
        // Non mi interessa se è chunk null o dati veri, il DB gestisce l'append.
        if (chunk != NULL) {
            db.append(pid_mittente, chunk);
        }
        
        // Se è l'ultimo pezzo, lo dico al DB
        if (is_last) {
            db.set_complete(pid_mittente);
        }
        
        // 4. CHECK: Il messaggio che volevo IO è pronto?
        if (db.is_ready(target_sender)) {
            return db.extract(target_sender);
        }
    }
}
*/



/*
Dato un servizio di message passing asincrono, implementare (senza far uso di processi server) un servizio
semisincrono che fornisce le seguenti funzioni:
sssend(msg_t msg, pid_t dest)
msg_t ssrecv(pid_t sender)
Se ci sono meno di 7 messaggi inviati dal processo A al processo B tramite la chiamata sssend non ancora ricevuti da B
tramite la ssrecv la chiamata sssend non è bloccante. Se ci sono 7 messaggi non ancora ricevuti la chiamata sssend è
bloccante. Il parametro sender della funzione ssrecv è l'identificativo di un processo mittente; il caso ANY non è
consentito.
*/


/* STRUTTURE DATI LOCALI (PER PROCESSO)
   Poiché non c'è memoria condivisa, ogni processo ha le sue variabili statiche/globali.
*/

// Costante per distinguere i tipi di messaggio
#define TYPE_DATA 1
#define TYPE_ACK  2

// Struttura del messaggio arricchita per distinguere Dati da ACK
struct packet_t {
    int type;      // TYPE_DATA o TYPE_ACK
    msg_t payload; // Il messaggio vero e proprio (vuoto se ACK)
};

// 1. Gestione Crediti (Finestra di invio)
// Mappa: PID Destinatario -> Crediti residui (Inizialmente 7 per tutti)
// Se non esiste la chiave, assumiamo 7.
Map<pid_t, int> credits;

// 2. Buffer per messaggi DATI letti "per sbaglio" mentre aspettavamo ACK
// Mappa: PID Mittente -> Coda di messaggi pendenti
Map<pid_t, Queue<msg_t>> pending_data;


// --- FUNZIONE DI INVIO ---
void sssend(msg_t msg, pid_t dest) {
    
    // Inizializzazione crediti se è la prima volta che scrivo a dest
    if (!credits.exists(dest)) credits[dest] = 7;

    // SE NON HO CREDITI, DEVO BLOCCARMI E ASPETTARE UN ACK
    while (credits[dest] <= 0) {
        
        // Aspetto un messaggio da 'dest'. 
        // ATTENZIONE: Potrebbe essere un ACK (quello che voglio) 
        // oppure un messaggio DATI (se dest mi sta scrivendo contemporaneamente).
        packet_t pkt = arecv(dest); // arecv qui è quella di sistema modificata per tornare packet_t
        
        if (pkt.type == TYPE_ACK) {
            // Evviva! Si è liberato un posto.
            credits[dest]++;
        } 
        else if (pkt.type == TYPE_DATA) {
            // Accidenti, è un messaggio dati per me. Non posso gestirlo ora 
            // perché sono dentro la send, ma non posso perderlo.
            // Lo salvo nel buffer per la futura ssrecv.
            pending_data[dest].enqueue(pkt.payload);
        }
    }

    // Ora ho sicuramente dei crediti (> 0)
    packet_t outgoing;
    outgoing.type = TYPE_DATA;
    outgoing.payload = msg;
    
    // Invio asincrono
    asend(outgoing, dest);
    
    // Consumo un credito
    credits[dest]--;
}


// --- FUNZIONE DI RICEZIONE ---
msg_t ssrecv(pid_t sender) {
    msg_t msg_to_return;
    bool found = false;

    // FASE 1: Controllo se ho messaggi già bufferizzati (letti dalla sssend)
    if (!pending_data[sender].isEmpty()) {
        msg_to_return = pending_data[sender].dequeue();
        found = true;
    }

    // FASE 2: Se non ho nulla nel buffer, devo leggere dalla rete
    while (!found) {
        packet_t pkt = arecv(sender);

        if (pkt.type == TYPE_DATA) {
            // È quello che cercavo!
            msg_to_return = pkt.payload;
            found = true;
        } 
        else if (pkt.type == TYPE_ACK) {
            // È un ACK relativo a un messaggio che IO ho mandato a LUI.
            // Devo processarlo subito per non bloccare i miei futuri invii.
            if (!credits.exists(sender)) credits[sender] = 7;
            credits[sender]++;
            // Continuo il while finché non trovo un DATA
        }
    }

    // FASE 3: Protocollo Semisincrono
    // Ho consumato un messaggio, devo mandare l'ACK al mittente
    // affinché lui possa riavere il credito.
    packet_t ack_pkt;
    ack_pkt.type = TYPE_ACK;
    ack_pkt.payload = NULL;

    asend(ack_pkt, sender);

    return msg_to_return;
}


/*
Usando i semafori implementare la classe nas712 (not a semaphore 7 1/2).
class nas712:
 __init__(value)
 naP()
 naV()
nas712 si comporta come un semaforo ma ci possono essere al più 7 processi bloccati. Quando ci sono 7 processi
bloccati una ulteriore naP non è bloccante e causa la riattivazione di tutti i (7) processi bloccati.
*/

class nas712 {
    int value;
    semaphore mutex(1);
    Queue<semaphore> sb; // Coda di semafori privati

    // Init
    nas712(int v) { value = v; }

    void naP() {
        mutex.P();
        
        if (value <= 0) {
            // Caso ROSSO
            if (sb.size() >= 7) {
                // --- CASO SPECIALE: SBLOCCO DI MASSA ---
                // "Una ulteriore naP non è bloccante e riattiva tutti"
                
                while (!sb.isEmpty()) {
                    semaphore s = sb.dequeue();
                    s.V(); // Sveglio i dormienti
                }
                // Esco senza bloccarmi e senza toccare value
                mutex.V();
            } 
            else {
                // --- CASO NORMALE: MI BLOCCO ---
                semaphore s = new semaphore(0);
                
                // NOTA: Usare 'sb', non 'q' (era un typo)
                sb.enqueue(s); 
                
                mutex.V(); // Rilascio il lock globale
                
                s.P(); // Mi addormento
                
                // --- RISVEGLIO ---
                // Importante: Deallocare il semaforo privato per non perdere memoria
                delete s; 
            }
        } 
        else {
            // Caso VERDE
            value--;
            mutex.V();
        }
    }

    void naV() {
        mutex.P();
        
        if (!sb.isEmpty()) {
            // PASSAGGIO DEL TESTIMONE
            // Sveglio il primo in coda. NON incremento value.
            // La risorsa che io rilascio viene data direttamente a lui.
            semaphore s = sb.dequeue();
            s.V();
        } 
        else {
            // NESSUNO IN CODA
            // Incremento il valore del semaforo
            value++;
        }
        
        mutex.V();
    }
}


//Esame 10/09/2024
/*
 Implementare il monitor firstlast che ha 3 procedure entry:
void addfirst(int val);
void addlast(int val);
int getboth(void);
Quando un processo chiama la procedure entry getboth deve attendere che ci sia almeno un processo che ha
chiamato la addfirst e uno che ha chiamato la addlast. La funzione getboth deve sbloccare il primo processo fra
quelli in attesa per aver chiamato addfirst e l'ultimo fra quelli in attesa per aver chiamato addlast. Il valore di ritorno
della getboth è la somma dei parametri passati alla addfirst e addlast dai processi sbloccati.
I processi che chiamano la addfirst o la addlast devono attendere di essere riattivati da una chiamata getboth.
*/

monitor firstlast {
    // Struttura per gestire le "Private Conditions"
    struct Proc {
        int value;    // Il valore portato dal processo
        condition c;  // Su cui il processo si addormenterà
    };

    // Strutture dati
    queue of Proc qFirst; // FIFO per addfirst (sblocca il primo)
    stack of Proc sLast;  // LIFO per addlast (sblocca l'ultimo)
    
    // Condizione per getboth: aspetta che ci sia qualcuno in entrambe
    condition ok2getboth;

    procedure entry void addfirst(int val) {
        // 1. Creazione richiesta e condizione privata
        Proc p = new Proc;
        p.value = val;
        
        // 2. Inserimento nella struttura (PRIMA di dormire)
        qFirst.enqueue(p);
        
        // 3. Controllo se posso svegliare una getboth
        // Se c'è almeno un 'last' in attesa, la coppia è completa
        if (sLast.size() > 0) {
            ok2getboth.signal();
        }
        
        // 4. Attesa sulla condizione PRIVATA
        p.c.wait();
        
        // 5. Risveglio e uscita
        // (p viene distrutta/liberata automaticamente o dal garbage collector)
    }

    procedure entry void addlast(int val) {
        Proc p = new Proc;
        p.value = val;
        
        // 2. Inserimento nello stack (LIFO)
        sLast.push(p);
        
        // 3. Controllo incrociato
        if (qFirst.size() > 0) {
            ok2getboth.signal();
        }
        
        // 4. Attesa privata
        p.c.wait();
    }

    procedure entry int getboth(void) {
        // 1. Attesa: devo avere almeno uno in coda E uno nello stack
        // Uso WHILE per semantica Mesa
        while (qFirst.isEmpty() || sLast.isEmpty()) {
            ok2getboth.wait();
        }

        // 2. Estrazione
        // Prendo il primo della coda (FIFO)
        Proc pF = qFirst.dequeue();
        // Prendo l'ultimo dello stack (LIFO - Top)
        Proc pL = sLast.pop();

        // 3. Calcolo somma
        int somma = pF.value + pL.value;

        // 4. Risveglio i partner
        // Uso le loro condizioni private specifiche
        pF.c.signal();
        pL.c.signal();

        return somma;
    }
}



/*
Dato un servizio di message passing asincrono scrivere un servizio di message passing asincrono
alternato (senza fare uso di processi server).
void altsend(msg_t msg, pid_t destination)
msg_t altrecv(pid_t sender)
La prima chiamata di altrecv deve restituire il primo messaggio fra quelli in attesa (spediti dal mittente sender o da
qualsiasi processo se sender==ANY). La seconda chiamata di altrecv deve restituire l'ultimo fra i messaggi in attesa, la
terza chiamata deve restituire il primo, la quarta chiamata l'ultimo e così via.
*/


/* STRUTTURE DATI LOCALI */

// Definiamo un messaggio speciale per il flush
#define MSG_TAG_TYPE 999 

// Il DB deve mantenere l'ordine globale di arrivo per gestire ANY correttamente.
// Una semplice lista/deque di messaggi è sufficiente.
// Ogni elemento salva: {sender_pid, message_body}
Deque<packet_t> local_db; 

// Variabile di stato per l'alternanza (0 = First, 1 = Last)
// Deve essere globale o static dentro la funzione
int toggle_mode = 0; 

// --- FUNZIONE SEND (Wrapper Semplice) ---
void altsend(msg_t msg, pid_t destination) {
    // Aggiungo il PID mittente nel payload o uso la primitiva di sistema
    // Qui assumiamo che asend invii <pid, msg>
    asend(msg, destination);
}

// --- FUNZIONE RECV ALTERNATA ---
msg_t altrecv(pid_t sender) {
    
    // 1. FASE DI FLUSH (SNAPSHOT)
    // Mando un messaggio speciale a me stesso per "marcare" la fine 
    // dei messaggi attualmente in attesa.
    packet_t marker;
    marker.type = MSG_TAG_TYPE;
    marker.sender = getpid();
    
    asend(marker, getpid()); 

    // Svuoto la mailbox di sistema nel mio DB locale finché non trovo il marker
    while (true) {
        packet_t pkt = arecv(ANY); // Leggo tutto
        
        if (pkt.type == MSG_TAG_TYPE && pkt.sender == getpid()) {
            break; // Ho finito lo snapshot dei messaggi presenti
        }
        
        // Salvo tutto ciò che non è il marker
        local_db.push_back(pkt);
    }

    // 2. FASE DI RICERCA (FETCH)
    // Ora local_db contiene tutti i messaggi che erano in attesa + quelli vecchi non ancora consumati.
    
    while (true) {
        packet_t found_pkt;
        bool found = false;
        
        // Cerco nel DB in base alla modalità (First o Last) e al sender
        if (toggle_mode == 0) { 
            // --- MODO FIRST (FIFO) ---
            // Cerco il PRIMO messaggio che corrisponde al sender
            found_pkt = local_db.findAndRemoveFirst(sender); 
        } 
        else { 
            // --- MODO LAST (LIFO) ---
            // Cerco l'ULTIMO messaggio che corrisponde al sender
            found_pkt = local_db.findAndRemoveLast(sender); 
        }

        if (found_pkt != NULL) {
            // Trovato! Inverto la modalità per la prossima volta e ritorno
            toggle_mode = 1 - toggle_mode; 
            return found_pkt.msg;
        }

        // 3. FASE BLOCCANTE (Se il DB non aveva nulla)
        // Se siamo qui, non c'erano messaggi per 'sender' nello snapshot.
        // Dobbiamo aspettare nuovi messaggi dalla rete.
        
        packet_t new_pkt = arecv(ANY); // Mi blocco qui
        
        // Appena arriva un messaggio, lo aggiungo al DB e ricomincio il ciclo.
        // Nota: non serve controllare se è un marker, perché i marker li mando solo io.
        local_db.push_back(new_pkt);
        
        // Ritorno su all'inizio del while(true) per vedere se questo 
        // nuovo messaggio soddisfa la richiesta.
    }
}


/*
Scrivere il monitor urgentsem che implementi un servizio di semafori con supporto di P urgente.
il monitor ha tre procedure entry e un costruttore:
void init(int initvalue)
void P(void)
void UP(void)
void V(void)
Vale l'invariante initvalue + NV >= NP + NUP (dove NX indica il numero di processi che hanno completato l'operazione X).
UP è una variante della P di tipo urgente. Quando rispettando l'invariante sia possibile scegliere fra un processo in attesa
per una chiamata P e uno in attesa per UP questo ultimo deve essere riattivato. Fra processi in attesa per P così come fra
processi in attesa per UP la riattivazione deve avvenire in ordine FIFO.
*/

monitor urgentsem{
    condition ok2P;
    condition ok2UP;
    int sem;
    int wp = 0;
    int wup = 0;
}

void init(int initvalue){
    sem = initvalue;
}

procedure_entry void P(void){
    if (sem > 0) sem--;
    else {
        wp++;
        ok2P.wait();
    }
}

procedure_entry void UP(void){
    if (sem > 0) sem--;
    else {
        wup++;
        ok2UP.wait();
    }
}

procedure_entry void V(void){
    if (wup > 0) {
        wup--;
        ok2UP.signal();
    } else if (wp > 0) {
        wp--;
        ok2P.signal();
    } else sem++;
}



/*
 Facendo uso di semafori scrivere una funzione syncvalue:
int syncvalue(int key)
la funzione syncvalue è sempre bloccante. Quando il valore del parametro key è diverso da quello della precedente
chiamata il processo prima di bloccarsi riattiva tutti i processi in attesa. Il valore di ritorno è il numero di processi con lo
stesso valore key sbloccati. Per esempio:
P chiama syncvalue(42), si blocca.
Q chiama syncvalue(42), si blocca.
R chiama syncvalue(44) sblocca P e Q poi si blocca. Il valore di ritorno per P e Q è 2.
T chiama syncvalue(46), sblocca R che ritorna 1 e si blocca.
Q chiama syncvalue(46), si blocca.
P chiama syncvalue(46), si blocca
V chiama syncvalue(0), sblocca T, Q e P (valore di ritorno: 3) poi si blocca...
*/

semaphore s(0);
semaphore mutex(1);
int last = -1; //supponendo che alla prima chiamata non si possa chiare il numero assegnato a last
int count = 0;

int syncvalue(int key){
    int static ret = 0;
    mutex.P();
    if (last == key){
        count ++;
        mutex.V();
        s.P();
    } else if (count == 0) { //lo eseguo solo nel caso iniziale, perché poi ci sarà sempre un processo in attesa
        count++;
        last = key;
        mutex.V();
        s.P();
    }
    else {
        ret = count;
        for (int i = 0; i < count; i++){
            s.V();
        }
        count = 1;
        last = key;
        mutex.V();
        s.P();
    }
    return ret;
}


//Solizione alternativa

/* Struttura per gestire un gruppo di processi con la stessa chiave */
struct Group {
    int key;            // La chiave del gruppo
    int count;          // Quanti processi ci sono
    semaphore sem(0);   // Semaforo privato del gruppo
};

// Puntatore al gruppo attualmente in fase di accumulo
Group *currentGroup = new Group(-1, 0); // Init fittizio
semaphore mutex(1);

int syncvalue(int key) {
    mutex.P();

    // 1. CONTROLLO CAMBIO CHIAVE
    // Se la chiave è diversa E c'è qualcuno nel gruppo precedente...
    if (key != currentGroup->key && currentGroup->count > 0) {
        
        // FASE DI FLUSH (Sblocco i vecchi)
        Group *oldGroup = currentGroup;
        
        // Sveglio tutti i processi del vecchio gruppo
        for (int i = 0; i < oldGroup->count; i++) {
            oldGroup->sem.V();
        }

        // Creo un NUOVO gruppo per il processo corrente (e i futuri)
        currentGroup = new Group(key, 0);
        
        // Nota: oldGroup rimane in memoria finché l'ultimo processo 
        // non esce (in C++ servirebbe un meccanismo di garbage collection 
        // o reference counting, ma in pseudocodice OS va bene così).
    }
    else if (currentGroup->count == 0) {
        // Gestione primo avvio o gruppo vuoto: aggiorno solo la chiave
        currentGroup->key = key;
    }

    // 2. AGGIUNTA AL GRUPPO CORRENTE
    currentGroup->count++;
    
    // Salvo il puntatore al MIO gruppo in una variabile locale.
    // Questo è fondamentale: anche se 'currentGroup' cambia globalmente 
    // mentre dormo, 'myGroup' punterà ancora alla mia struttura corretta.
    Group *myGroup = currentGroup;

    mutex.V();

    // 3. BLOCCO
    // Mi addormento sul semaforo del MIO gruppo
    myGroup->sem.P();

    // 4. RITORNO
    // Al risveglio, leggo il conteggio dal mio gruppo (che è stabile)
    return myGroup->count;
}


/*
Scrivere il monitor rgbsum che fornisce una procedure entry:
#define red 0
#define green 1
#define blue 2
double rgb(int color, double value)
I processi che usano il monitor rgbsum devono sommare i valori delle sequenze di chiamate dello stesso colore (red,
green o blue). La funzione rgb è sempre bloccante. Solo quando una sequenza di chiamate dello stesso colore viene
interrotta da una chiamata di colore diverso tutti i processi in attesa vengono sbloccati e rgb restituisce la somma dei
parametri 'value'.
Esempio: Il processo P chiama rgb(red, 2) -> si blocca. il processo Q chiama rgb(red, 4) ->si blocca. Il processo R chiama
rgb(blue, 1) sblocca i due processi P e Q che hanno chiamato rgb con parametro red, ad entrambi rgb ritorna il valore 6
(2 + 4). poi R si blocca. se ora un altro processo T chiama rgb(green, 39) il processo R continua e rgb ritorna 1 mentre R si
ferma. Ora i processi W,X,Y chiamano tutti rgb(green, 1) bloccandosi. Il processo Z chiamando rgb(red, 0) sblocca R,W,X,Y,
rgb restituisce a questi processi il valore 42 e Z si ferma
*/

monitor rgsum{
    #define red 0
    #define green 1
    #define blue 2

    struct data{
        int col;
        int count;
        condition c;
        double ret;
    };
    
    data *curcolor = new data;

}

init {
    curcolor->col = -1;
    curcolor->count = 0;
    curcolor->ret = 0;
}

procedure_entry double rgb(int color, double value){
     data *myc;
    if (curcolor->col == color){
        myc = curcolor;
        myc->count++;
        myc->ret = myc->ret+value;
        myc->c.wait();
    } else if (curcolor->count == 0){
        curcolor->col = color;
        curcolor->count++;
        curcolor->ret = value;
        myc = curcolor;
        myc->c.wait();
    } else {
        for (int i = 0; i < curcolor->count; i++){
            curcolor->c.signal();
        }
        myc = new data;
        myc->col = color;
        myc->ret = value;
        myc->count = 1;
        curcolor = myc;
        myc->c.wait();
    }
    return myc->ret;
}


/*
 Sia dato un sistema di message passing asincrono con duplicazione dei messaggi.
dsnd(msg_t msg, pid_t dest)
msg_t drecv(pid_t sender)
I messaggi spediti con dsend verranno sicuramente ricevuti almeno una volta ma possono essere ricevuti più volte. È
garantita la consegna FIFO.
Implementare un sistema di message passing asincrono (classico). (non fare uso di processi server)
*/

/* STRUTTURE DATI LOCALI PER PROCESSO */

// Sender: Ricorda l'ultimo numero usato per ogni destinatario
// PID Destinatario -> Ultimo SeqNum inviato
Map<pid_t, int> next_seq_num_out; 

// Receiver: Ricorda il prossimo numero atteso da ogni mittente
// PID Mittente -> Prossimo SeqNum atteso
Map<pid_t, int> expected_seq_num_in;


// --- FUNZIONE DI INVIO ---
void standard_send(msg_t msg, pid_t dest) {
    
    // 1. Recupero o inizializzo il contatore per questo destinatario
    if (!next_seq_num_out.exists(dest)) {
        next_seq_num_out[dest] = 0;
    }
    
    int my_seq = next_seq_num_out[dest];
    
    // 2. Invio il messaggio "arricchito" col numero di sequenza
    // Packet = <PID_Mittente, SeqNum, Dati>
    dsend(<getpid(), my_seq, msg>, dest);
    
    // 3. Incremento il contatore per il prossimo messaggio
    next_seq_num_out[dest]++;
}


// --- FUNZIONE DI RICEZIONE ---
msg_t standard_recv(pid_t filter_sender) {
    
    // Inizializzo il contatore se è la prima volta che ricevo da filter_sender
    // (Nota: se filter_sender è ANY la logica si complica leggermente, 
    // qui assumiamo un sender specifico o gestiamo la mappa dinamicamente)
    
    while (true) {
        // 1. Ricevo dal livello basso (che può contenere duplicati)
        <pid_mittente, seq_num, body> = drecv(filter_sender);
        
        // Inizializzo contatore locale se non esiste per questo mittente
        if (!expected_seq_num_in.exists(pid_mittente)) {
            expected_seq_num_in[pid_mittente] = 0;
        }
        
        // 2. Controllo il Numero di Sequenza
        int expected = expected_seq_num_in[pid_mittente];
        
        if (seq_num == expected) {
            // CASO A: Messaggio NUOVO ed ATTESO.
            // 1. Aggiorno il mio contatore (ora mi aspetto il prossimo)
            expected_seq_num_in[pid_mittente]++;
            
            // 2. Restituisco il messaggio all'utente
            return body;
        } 
        else if (seq_num < expected) {
            // CASO B: Messaggio VECCHIO (Duplicato).
            // Esempio: Aspetto il 5, mi arriva il 4 (o il 3, o di nuovo il 4).
            // AZIONE: Lo scarto silenziosamente e continuo il while.
            continue; 
        }
        
        // CASO C (seq_num > expected): 
        // In un sistema FIFO garantito come questo, non dovrebbe succedere 
        // di ricevere il 6 prima del 5. Se succedesse, andrebbe bufferizzato,
        // ma la traccia garantisce l'ordine FIFO.
    }
}

/*
Scrivere il monitor ds (dispatchstring) che consenta di trasferire stringhe di caratteri fra processi. Il monitor
ha quattro procedure entry:
void startsend(void)
void sendchar(char c)
void startrecv(void)
char recvchar(void)
Quando un processo vuole spedire una stringa chiama la funzione startsend poi tramite sendchar spedisce uno ad
uno i caratteri della stringa e infine il carattere 0 per indicare la fine della stringa. Similmente quando un processo vuole
ricevere una stringa chiama la funzione startrecv, riceve uno ad uno i caratteri usando la recvchar. La ricezione del
carattere 0 indica la fine della stringa.
Il monitor trasferisce una stringa alla volta e deve usare un buffer di un solo carattere (non può memorizzare vettori o
stringhe di caratteri).
*/

monitor ds {
    // VARIABILI DI STATO
    // Sessione: true se c'è una trasmissione di stringa in corso
    bool active_sender;    
    bool active_receiver;  
    
    // Buffer: dimensione 1
    char buffer;           
    bool full;             

    // CONDIZIONI
    condition ok2start_send; // Coda per iniziare a inviare (Sessione)
    condition ok2start_recv; // Coda per iniziare a ricevere (Sessione)
    
    condition ok2write;      // Coda per scrivere nel buffer (Carattere)
    condition ok2read;       // Coda per leggere dal buffer (Carattere)

    // INIZIALIZZAZIONE
    init {
        active_sender = false;
        active_receiver = false;
        full = false;
    }

    // --- LATO MITTENTE ---

    procedure entry void startsend() {
        // Mutua esclusione sulla sessione di invio
        while (active_sender) {
            ok2start_send.wait();
        }
        active_sender = true;
    }

    procedure entry void sendchar(char c) {
        // Produttore: aspetto spazio nel buffer
        while (full) {
            ok2write.wait();
        }

        buffer = c;
        full = true;
        
        // Ho messo un dato, sveglio il consumatore
        ok2read.signal();

        // Controllo fine stringa
        if (c == '\0') {
            // Rilascio la sessione
            active_sender = false;
            // Sveglio il prossimo sender in coda (se c'è)
            ok2start_send.signal();
        }
    }

    // --- LATO RICEVENTE ---

    procedure entry void startrecv() {
        // Mutua esclusione sulla sessione di ricezione
        while (active_receiver) {
            ok2start_recv.wait();
        }
        active_receiver = true;
    }

    procedure entry char recvchar() {
        // Consumatore: aspetto un dato
        while (!full) {
            ok2read.wait();
        }

        char c = buffer;
        full = false;

        // Ho liberato spazio, sveglio il produttore
        ok2write.signal();

        // Controllo fine stringa
        if (c == '\0') {
            // Rilascio la sessione
            active_receiver = false;
            // Sveglio il prossimo receiver in coda
            ok2start_recv.signal();
        }

        return c;
    }
}

/*
Il monitor swapobj ha due procedure entry:
void swapa(obj_t *in, obj_t *out);
void swapb(obj_t *in, obj_t *out);
I processi di tipo A chiamano la swapa e quelli di tipo B chiamano la swapb. In ordine FIFO i processi che chiamano la
swapa e quelli che chiamano la swapb copiano vicendevolmente il valore degli oggetti passati come parametro:
Il primo processo che chiama la swapa copia il valore del proprio parametro out nel parametro in del primo processo
che ha chiamato la swapb e viceversa (copia il parametro out del primo swapb nel parametro in del primo swapa).
Similmente devono fare il secondo processo che chiama swapa con secondo che chiama swapb e così via.
*/

monitor swapobj {
    
    // Struttura per lo scambio (Rendezvous Point)
    struct Request {
        obj_t val_offerto;   // Il valore portato dal processo in attesa (OUT del waiter)
        obj_t val_ricevuto;  // Il valore lasciato dal processo arrivato (OUT del waker)
        condition c;         // Condition privata su cui dormire
    };

    // Code per i processi in attesa
    queue of Request* queueA;
    queue of Request* queueB;

    // PROCEDURA PER I PROCESSI TIPO A
    procedure entry void swapa(obj_t *in, obj_t *out) {
        
        // CASO 1: C'è un processo B che mi sta già aspettando?
        if (!queueB.isEmpty()) {
            // Estraggo la richiesta del partner B
            Request *reqB = queueB.dequeue();
            
            // 1. Prendo il valore che B ha portato (copio nel mio IN)
            *in = reqB->val_offerto;
            
            // 2. Lascio a B il valore che ho portato io (copio nel suo slot di ricezione)
            reqB->val_ricevuto = *out;
            
            // 3. Sveglio B
            reqB->c.signal();
            
            // Ho finito, esco.
        } 
        // CASO 2: Nessuno in B, devo aspettare (sono il primo della coppia)
        else {
            // Creo la mia richiesta
            Request *myReq = new Request;
            myReq->val_offerto = *out; // Salvo il mio valore per chi arriverà
            
            // Mi accodo
            queueA.enqueue(myReq);
            
            // Dormo
            myReq->c.wait();
            
            // AL RISVEGLIO:
            // Il processo B che mi ha svegliato ha messo il suo valore in 'val_ricevuto'
            *in = myReq->val_ricevuto;
            
            // Pulizia (opzionale, dipende dal linguaggio)
            delete myReq;
        }
    }

    // PROCEDURA PER I PROCESSI TIPO B (Simmetrica)
    procedure entry void swapb(obj_t *in, obj_t *out) {
        
        // CASO 1: C'è un processo A in attesa?
        if (!queueA.isEmpty()) {
            Request *reqA = queueA.dequeue();
            
            // Prendo da A
            *in = reqA->val_offerto;
            
            // Do ad A
            reqA->val_ricevuto = *out;
            
            // Sveglio A
            reqA->c.signal();
        } 
        // CASO 2: Aspetto
        else {
            Request *myReq = new Request;
            myReq->val_offerto = *out;
            
            queueB.enqueue(myReq);
            
            myReq->c.wait();
            
            *in = myReq->val_ricevuto;
            
            delete myReq;
        }
    }
}

/*
 I semafori ennari possono assumere i valori 0,...,N-1 e hanno la seguente interfaccia:
class ensem:
 void __init__(int N, int init); //costruttore
 void P(void)
 void V(void)
L'invariante dei semafori ennari è:
0 <= nV + init <= nP + N - 1
dove nP è il numero di operazioni P completate, nV il numero delle operazioni V completate e init è il valore iniziale del
semaforo. Semafori ennari e semafori ordinari hanno lo stesso potere espressivo?
*/

//per domostrare che hanno lo stesso poter espressivo devo implementare uno con l'altro e viceversa
//(i semafori generali possono avere valori da 0 fino a inf., non hanno un limite)

//implemento questi semafori tramite i generali:

/* DIMOSTRAZIONE EQUIVALENZA POTERE ESPRESSIVO
   Semafori Ennari (Bounded) <-> Semafori Generali (Counting)
*/

// ==========================================================
// PARTE 1: Implementare un Semaforo Ennario usando Generali
// ==========================================================
/*
  Logica:
  - Il semaforo generale 's' gestisce nativamente il blocco a 0 (limite inferiore).
  - Dobbiamo aggiungere noi il controllo per il limite superiore (N-1).
  - Usiamo un intero 'val' protetto da mutex per sapere quanto vale il semaforo.
*/

class EnnarySem {
    int max_N;
    int current_val;
    
    semaphore s;     // Semaforo Generale (Standard)
    semaphore mutex; // Mutex per proteggere current_val

    // Costruttore
    void init(int N, int init_val) {
        max_N = N;
        current_val = init_val;
        
        // Inizializziamo il semaforo generale al valore iniziale
        s = new semaphore(init_val); 
        mutex = new semaphore(1);
    }

    void P() {
        // 1. Usiamo il semaforo generale per bloccarci se siamo a 0.
        //    Questo è thread-safe e gestisce la coda nativamente.
        s.P();

        // 2. Aggiorniamo il nostro contatore ombra
        mutex.P();
        current_val--;
        mutex.V();
    }

    void V() {
        mutex.P();
        
        // 3. Controllo Limite Superiore (L'invariante Ennario)
        // Possiamo fare V solo se non superiamo N-1
        if (current_val < max_N - 1) {
            s.V();          // Sblocca o incrementa
            current_val++;
        } 
        // Se current_val == N-1, la V viene ignorata (o dovrebbe dare errore),
        // perché un semaforo Ennario non può superare il massimo.
        
        mutex.V();
    }
};


// ==========================================================
// PARTE 2: Implementare un Semaforo Generale usando Ennari
// ==========================================================
/*
  Logica:
  - Non possiamo usare il conteggio interno del semaforo Ennario per contare 
    fino a 1000, perché si bloccherebbe a N-1.
  - Usiamo i semafori Ennari solo come "Mattoncini Binari" (N=2):
    1. Un Ennario(2, 1) che agisce da MUTEX.
    2. Un Ennario(2, 0) che agisce da CODA DI ATTESA (Delay).
  - Il conteggio vero (che va a infinito) lo teniamo in un intero 'count'.
*/

class GeneralSem {
    int count;
    
    // Usiamo EnnarySem come se fossero binari
    ensem mutex; // Init(2, 1) -> Aperto
    ensem delay; // Init(2, 0) -> Chiuso

    void init(int init_val) {
        count = init_val;
        mutex = new ensem(2, 1); // Funziona da Mutex
        delay = new ensem(2, 0); // Funziona da Wait Queue
    }

    void P() {
        mutex.P(); // Lock
        count--;
        
        if (count < 0) {
            mutex.V(); // Rilascio il lock prima di dormire
            delay.P(); // Mi blocco sulla coda ennaria
        } else {
            mutex.V(); // Se c'era posto, esco subito
        }
    }

    void V() {
        mutex.P(); // Lock
        count++;
        
        if (count <= 0) {
            // Se count era negativo, significa che c'è qualcuno bloccato su 'delay'.
            // Lo sveglio.
            delay.V();
        }
        
        mutex.V();
    }
};

/*
Sia dato un sistema nel quale è presente un meccanismo di message passing asincrono che consente di
inviare messaggi di lunghezza massima 256 byte e che ha le seguenti primitive:
lasend(byte *msg, pid_t dest)
byte *larecv(pid_t sender)
I messaggi che larecv riceve da ogni mittente sono consegnati in ordine FIFO.
In tale sistema scrivere (senza fare uso di processi server) un servizio di message passing asincrono per messaggi di
lunghezza arbitraria:
asend(msg_t *msg, pid_t dest)
msg_t arecv(pid_t sender)
sapendo che sizeof(pid_t) vale 4 e che esistono funzioni per calcolare la lunghezza di un messaggio e per scomporre e
ricomporre sottosequenze dei messaggi (definite per queste funzioni l'API che ritenete più opportuna).
*/

/* * DEFINIZIONE PROTOCOLLO DI BASSO LIVELLO
 * Dimensione massima: 256 byte
 * Header: PID (4 byte) + Flag (1 byte) = 5 byte
 * Payload utile: 256 - 5 = 251 byte
 */

#define MAX_PACKET_SIZE 256
#define HEADER_SIZE (sizeof(pid_t) + sizeof(bool))
#define MAX_PAYLOAD (MAX_PACKET_SIZE - HEADER_SIZE) // 251 byte

// Struttura che mappa esattamente il buffer di byte inviato
typedef struct {
    pid_t sender;      // 4 byte (Hint della traccia)
    bool is_last;      // 1 byte (Flag di fine messaggio)
    char data[MAX_PAYLOAD]; // 251 byte di dati
} Packet;


// --- FUNZIONE DI INVIO ---
void asend(msg_t *msg, pid_t dest) {
    // 1. Calcolo quanti pezzi servono
    int total_len = msg->length();
    int offset = 0;
    
    // Ciclo finché non ho spedito tutto
    // Nota: usando un do-while gestisco anche il caso di messaggio vuoto (0 byte)
    // che deve comunque mandare un pacchetto con is_last=true.
    do {
        Packet pkt;
        pkt.sender = getpid();
        
        // Calcolo quanto copiare in questo chunk
        int remaining = total_len - offset;
        int chunk_size = (remaining > MAX_PAYLOAD) ? MAX_PAYLOAD : remaining;
        
        // Riempio il payload
        // Ipotizziamo una funzione di copia o metodo dell'oggetto msg
        msg->copy_to(pkt.data, offset, chunk_size);
        
        // Aggiorno offset
        offset += chunk_size;
        
        // 2. Imposto il flag
        // Se ho copiato tutto (offset == total_len), questo è l'ultimo
        pkt.is_last = (offset >= total_len);
        
        // 3. Invio fisico (casting a byte*)
        lasend((byte*)&pkt, dest);
        
    } while (offset < total_len);
}


// --- FUNZIONE DI RICEZIONE ---
msg_t arecv(pid_t sender) {
    // Lista per accumulare i pezzi ricevuti
    List chunks; 
    bool complete = false;
    
    while (!complete) {
        // 1. Ricezione dal livello basso (Bloccante)
        // Riceve un buffer di 256 byte grezzi
        byte *raw_buffer = larecv(sender);
        
        // 2. Casting (Interpretazione dei byte)
        // Trasformiamo i byte grezzi nella nostra struttura Packet
        Packet *pkt = (Packet*)raw_buffer;
        
        // Controllo di sicurezza (opzionale ma consigliato)
        if (pkt->sender != sender) {
            // Errore grave: il sistema ha consegnato il mittente sbagliato
            // o gestione di un eventuale ANY (se supportato)
        }
        
        // 3. Accumulo dati
        // Estraiamo solo la parte valida del payload (potrebbe essere meno di 251 byte se è l'ultimo)
        // Qui assumiamo di sapere la lunghezza o che il chunk sia una stringa/buffer gestito
        chunks.append(pkt->data);
        
        // 4. Controllo Fine
        if (pkt->is_last) {
            complete = true;
        }
        
        // Importante: in C/C++ bisogna liberare la memoria ritornata da larecv 
        // se larecv alloca dinamicamente. Assumiamo di sì.
        free(raw_buffer);
    }
    
    // 5. Ricostruzione finale
    return chunks.unite();
}


/*
Scrivere il monitor choicesem che implementa un semaforo con scelta che ha le seguenti procedure entry:
void P(void)
void V(int n)
Il semaforo con scelta soddisfa l'invariante dei semafori ma i processi non vengono riattivati in ordine FIFO.
La funzione V se vi sono in attesa al più n processi riattiva il primo altrimenti viene riattivato quello in posizione n + 1 nella
sequenza di attesa.
es. se ci sono in attesa i processi A, B e C, la funzione V(0) attiverebbe A, V(1) attiverebbe B, V(2) attiverebbe C, per tutti i
valori del parametro maggiori di 2 verrebbe riattivato A.
*/

monitor choicsem{
    int val;
    queue of condition cond;
}
init (int iniz){
    val = iniz;
}

procedure_entry void P(void){
    if (val == 0){ // <= per robustezza, ma nell'invariante non può essere negativo
        condition c = new condition;
        cond.enqueue(c);
        c.wait();
    } else {
        val--;
    }
}

procedure_entry void V(int n){
    n++;
    if (!cond.isEmpty()){
        s = cond.size();
        if (n > s){
            condition c = cond.dequeue();
            c.signal();
        } else {
            condition c = cond.remove(n); //rimuove e ritorna l'ennesimo elemento, contando da 1, non da 0, per questo ho fatto n++
            c.signal();
        }
    } else {
        val++;
    }
}

/*
Un servizio di message passing asincrono esteso (XAMP) fornisce 4 chiamate:
• void xsend(msg_t msg, pid_t pid): spedisce il messaggio msg al processo pid
• msg_t xrecv(pid_t pid): riceve un messaggio da pid (o da chiuque se pid==0). E' una receive completamente
asincrona: se non c'è nessun messaggio da pid (o da chiunque se pid==0), xrecv restituisce NULL, non attende.
• int xcount(pid_t pid): ritorna il numero di messaggi in attesa di essere ricevuti provenienti da pid (o da
chiunque se pid==0).
• void xexpect(pid_t pid): attende che vi sia almeno un messaggio in attesa di essere ricevuto proveniente da
pid (o da chiunque se pid==0). Se un tale elemento esiste al momento della chiamata, xexpect non è
bloccante.
Il servizio XAMP ha lo stesso potere espressivo del message passing asincrono? (quello definito a lezione).
*/

//per poter dire che ha lo stesso potere espressivo devo poter implementare un sistema tramite l'altro e viceversa

//implemento XAMP tramite message passing asincrono

void xsend(msg_t msg, pid_t pid){
    asend(<getpid(), msg>,pid);
}

msg_t xrecv(pid_t pid){

}

int xcount(pid_t pid){

}

void xexpect(pid_t pid){
    if(xcount(pid)> 0) return;
    else arecv(pid);

}

//implemento message passing asincrono tramite XAMP

void asend(msg_t msg, pid_t pid){
    xsend(msg,pid);
}

msg_t arecv(pid_t pid){
    while(true){
        msg_t msg = xrecv(pid);
        if (msg != NULL) return msg;
        xexpect(pid);
    }
}

//non posso implementare xcount perché non ho modo di sapere quanti messaggi sono in attesa senza fare uso di processi server
//quindi non hanno lo stesso potere espressivo


/*
Il monitor AB gestisce l'accodamento limitato di due tipi di dati A e B. Il monitor prevede 3 procedure entry:
void AB.add2a(int a0, int a1)
void AB.addb(int b0)
void AB.geta2b(int *a0, int *b0, int *b1).
add2a aggiunge 2 elementi di tipo A, addb aggiunge un elemento di tipo B, geta2b restituisce un elemento di tipo A e
due di tipo B.
Il monitor può memorizzare al massimo MAX elementi di tipo A e MAX di tipo B. (MAX >= 2).
Se non sono disponibili almeno un elemento di tipo A e due di tipo B la funzione geta2b deve attendere.
Gli elementi devono essere restituiti in ordine FIFO così come le richieste pendenti per geta2b devono essere esaudite in
ordine FIFO.
*/

moitor AB{
    #define MAX = 10;
    int aA[MAX];
    int aB[MAX];
    int ca = -1;
    int cb = -1;
    condition ok2get;
    condition ok2adda;
    condition ok2addb;
}

procedure_entry void add2a(int a0, int a1){
    if (ca >= MAX-2){ // ca al massimo 7, non 8 o superiore
        ok2adda.wait(); //nel caso lo sia aspetto
    }
    ca++;
    aA[ca] = a0;
    if (cb > 0) ok2get.signal();
    ca++;
    aA[ca] = a1;
    if (cb > 0) ok2get.signal(); // non necessaria la signal due volte, ma va bene lo stesso
}

procedure_entry void addb(int b0){
    if (cb >= MAX-1){ //aspetto se cb = 9
        ok2addb.wait();
    } 
    cb++;
    aB[cb] = b0;
    if (cb > 0 and ca > -1) ok2get.signal();
}

procedure_entry void geta2b(int *a0, int *b0, int *b1).{
    if (!(cb > 0) or !(ca > -1)){
        ok2get.wait();
    }
    *a0 = aA[0];
    ca--;
    aA.shift_left();
    if (ca < MAX-2) ok2adda.signal();
    *b0 = aB[0];
    cb--;
    aB.shift_left();
    ok2addb.signal();
    *b1 = aB[0];
    cb--;
    aB.shift_left();
    ok2addb.signal();
}

//soluzione elegante

monitor AB {
    const int MAX = 10;
    
    // Code per i dati (FIFO implicito nella struttura)
    Queue<int> bufferA;
    Queue<int> bufferB;
    
    // Condition Variables
    condition ok2addA; // Aspetto spazio per A
    condition ok2addB; // Aspetto spazio per B
    condition ok2get;  // Aspetto dati (1A e 2B)

    procedure entry void add2a(int a0, int a1) {
        // Devo inserire 2 elementi. Aspetto finché non c'è spazio per 2.
        while (bufferA.size() + 2 > MAX) {
            ok2addA.wait();
        }

        bufferA.enqueue(a0);
        bufferA.enqueue(a1);

        // Ho aggiunto risorse. Se c'è un get in attesa e ho soddisfatto i requisiti...
        // Controllo: serve almeno 1 A (ce l'ho sicuro) e 2 B.
        if (bufferB.size() >= 2) {
            ok2get.signal();
        }
    }

    procedure entry void addb(int b0) {
        // Aspetto spazio per 1 elemento B
        while (bufferB.size() + 1 > MAX) {
            ok2addB.wait(); // CORRETTO: wait su B, non su A
        }

        bufferB.enqueue(b0);

        // Controllo se posso svegliare il consumatore
        // Serve 1 A e 2 B.
        if (bufferA.size() >= 1 && bufferB.size() >= 2) {
            ok2get.signal();
        }
    }

    procedure entry void geta2b(int *a0, int *b0, int *b1) {
        // Aspetto risorse: 1 tipo A e 2 tipo B
        while (bufferA.size() < 1 || bufferB.size() < 2) {
            ok2get.wait();
        }

        // Prelievo i dati e li passo ai puntatori del chiamante
        *a0 = bufferA.dequeue();
        *b0 = bufferB.dequeue();
        *b1 = bufferB.dequeue();

        // Ho liberato 1 posto in A -> Sveglio produttori A
        ok2addA.signal();
        
        // Ho liberato 2 posti in B -> Sveglio produttori B
        // Nota: Poiché addb inserisce 1 alla volta, potrei svegliarne anche due, 
        // ma signal() ne sveglia uno che poi (se c'è ancora spazio) sveglierà l'altro.
        // Per efficienza massima in questo caso specifico si potrebbe usare signal_all su B
        // o doppia signal, ma una signal è corretta per sbloccare la catena.
        ok2addB.signal();
        ok2addB.signal(); // Opzionale ma gentile: ho liberato 2 posti
    }
}

/*
Dato un servizio di message passing asincrono costruire un servizio di message passing completamente
asincrono a liste che abbia due metodi:
nbl_send(msg_t m, pid_t dest)
list of msg_t nbl_receive(pid_t sender)
La chiamata nbl_receive deve restituire la lista di tutti i messaggi ricevuti dal mittente specificato (sender) o la lista di
tutti i messaggi ricevuti se sender è -1 (ANY).
Il servizio è completamente asincrono perché se non vi sono messaggi che soddisfano la condizione richiesta
nbl_receive restituisce una lista vuota senza attendere.
*/

Map<pid_t, List<msg_t>> buffer; //mappa per la gestione dei messaggi, insieme di buffer, ordinati sul valore della chiave
List<pid_t>> send; //lista dei sender

buffer.exists(sender_pid) //per controllare se il buffer esiste, cerca nella lista send
buffer.delete(sender); //dealloca la lista di sender, e lo rimuove dalla lista dei sender send
send.isIn(sender) //constrolla nella lista send se c'è sender
buffer.newList(sender); // crea la lista con la chiave sender
buffer[sender].size(); //ritornala dimensione della lista con chiave sender
.append() //per aggiungere un elemento al buffer
.size() //restituisce la dimensione del buffer
.remove() //restituisce il primo elemento della lista, e lo rimuove

proces server(){
    while (true){
        <sender, msg> = arecv(ANY);
        if (!send.isIn(sender)) {
            send.append(sender); //tengo aggiornata la lista dei sender
            buffer.newList(sender); // crea la lista con la chiave sender
        }
        buffer[sender].append(msg);
    }
}


nbl_send(msg_t m, pid_t dest){
    asend(<getpid(), m>,dest);
}

list of msg_t nbl_receive(pid_t sender){
    if (sender != ANY){
        if (!send.isIn(sender)) return -1; //oppure [], comunque indichiamo la lista vuota
        else {
            List<msg_t>> ret = new List;
            int s = buffer[sender].size();
            for (int i = 0; i < s; i++){
                msg_t tmp = buffer[sender].remove(); //mi rimuove e ritorna il primo elemento del buffer, FIFO
                ret.append(tmp);
            }
            buffer.delete(sender); // elimino il buffer, così che se viene chiesto nuovamente senza essere reinizializzato ritorno -1;
            return ret;
        }
    } else {
        if (send.isEmpty()) return -1; //se chiamo la funzione exists senza argomento la funzione cercherà una qualsiasi lista
        List<msg_t>> ret = new List;
        for (int i = 0; i < send.size(); i++){
            int s = buffer.size(send.remove());
            for (int i = 0; i < s; i++){
                msg_t tmp = buffer[sender].remove(); //mi rimuove e ritorna il primo elemento del buffer, FIFO
                ret.append(tmp);
            }
            buffer.delete(sender);
        }
        return ret;
    }
}

//alcune imprecisioni ma l'idea è quella giusta, 7.5/10

//versione gemini
/* STRUTTURE DATI CONDIVISE */

// Mappa: PID -> Lista messaggi
// La mappa funge sia da storage che da indice dei mittenti esistenti
Map<pid_t, List<msg_t>> buffer; 

// Mutex per proteggere l'accesso concorrente alla mappa
Mutex mtx; 

// --- THREAD HELPER (Gira in background) ---
thread helper() {
    while (true) {
        // 1. Ricezione Bloccante (fuori dalla sezione critica)
        <pid_mittente, messaggio> = arecv(ANY);
        
        // 2. Sezione Critica: Aggiornamento Buffer
        mtx.lock();
        
        // Se è la prima volta che scrive, la mappa crea la lista automaticamente
        // (o usiamo una logica .exists() implicita)
        buffer[pid_mittente].append(messaggio);
        
        mtx.unlock();
    }
}

// --- FUNZIONI UTENTE ---

void nbl_send(msg_t m, pid_t dest) {
    asend(m, dest); // Wrapper semplice
}

List<msg_t> nbl_receive(pid_t sender) {
    List<msg_t> result = new List; // Lista vuota iniziale

    mtx.lock(); // INIZIO SEZIONE CRITICA

    // --- CASO 1: Mittente Specifico ---
    if (sender != ANY) {
        if (buffer.exists(sender)) {
            // Sposto tutti i messaggi nella lista risultato
            // (È meglio spostare l'intera lista piuttosto che copiare elemento per elemento)
            result = buffer[sender]; 
            
            // Rimuovo la voce dalla mappa (svuoto il buffer per quel mittente)
            buffer.remove(sender);
        }
        // Se non esiste, result rimane vuota (corretto secondo specifica)
    } 
    // --- CASO 2: ANY (-1) ---
    else {
        // Devo raccogliere TUTTI i messaggi da TUTTI i mittenti
        // Itero sulle chiavi della mappa
        foreach (pid_t key in buffer.keys()) {
            List<msg_t> partial = buffer[key];
            
            // Unisco alla lista risultato
            result.merge(partial);
        }
        // Svuoto completamente la mappa
        buffer.clear();
    }

    mtx.unlock(); // FINE SEZIONE CRITICA

    return result;
}


/*
Dato msg passing asincrono, implementare msg passing completamente asincrono.
*/

casend(msg_t msg, pid_t dest){
    asend(<getpid(), msg>, dest);
}

Map<pid_t, List <msg_t>> buffer;

List <msg_t> carecv(pid_t sender){
    if (sender == ANY) return []; //oppure -1, comunque indichiamo la lista vuota
    pid_t pid;
    msg_t msg;
    asend(<getpid(), TAG>, getpid()); //invio un messaggio di terminazione al server
    while (true){
        <pid, msg> = arecv(ANY);
        if (pid == getpid() and msg == TAG) break;
        if (pid is in buffer.keys()) buffer[pid].append(msg);
        else {
            new List <msg_t> l = [];
            l.append(msg);
            buffer[pid] = l;
        }
    }
    new List <msg_t> ret = [];
    if (buffer[sender].exists()) ret = buffer[sender];
    buffer[sender].delete();
    return ret;
}

/*
Dato un msg passing, implementare un msg passing LIFO
*/

void lasend(msg_t msg, pid_t dest){
    asend(<getpid(), msg>, dest);
}

Map<pid_t, Stack <msg_t>> buffer;

List<msg_t> larecv(pid_t sender){
    pid_t pid;
    if (sender == ANY) return []; //oppure -1, comunque indichiamo la lista vuota, non vogliamo gestire questo caso
    asend(<getpid(),TAG>, getpid());
    while (true){
        <pid, msg> = arecv(ANY);
        if (pid == getpid() and msg == TAG) break;
        else if (pid is in buffer.keys()) buffer[pid].push(msg);
        else {
            new Stack s = [];
            s.push(msg);
            buffer[pid] = s;
        }
    }
    new List<msg_t> ret = [];
    if (buffer[sender].exists()) {
        while (!buffer[sender].isEmpty()){
            ret.append(buffer[sender].pop());
        }
    }
    buffer[sender].delete();
    return ret; // se non c'è nulla ritorno la lista vuota, e suppongo che lo stack sia una lista in ordine LIFO
}