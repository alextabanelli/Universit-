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


monitor nmeet
wa: dynarray {int nwait, float sum, condition c} //.....simile ai dizionari di python
float average
procedur_entry nmeet(unsigned int n, float val){
    if (n not in wa){
        wa[n].nwait = 0;
        wa[n].sum = 0.0;
    }
    wa[n].nwait++;
    wa[n].sum+=val;
    if (n == wa[n].nwait){
        average = wa[n].sum/n;
        wa[n].c.signal()
        wa[n].sum = 0;
    }
    else {
        wa[n].c.wait();
        wa[n].c.signal();
    }
    wa[n].nwait--;
    return average;
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

monitor minlenbb{
    q: array[N] of queue;
    int tot = 0;
    condition ok2add;    //tot < N*NELEM
    condition ok2get;    //q[n].len() > 0
}


procedur_entry add(objtype obj){
    if (tot >= N*NELEM){
        ok2add.wait();
    }
    n = minindex(q);  //minindex la diamo per scontata se spieghiamo il suo funzionamento, funzione che ci ritorna l'indice che ha meno elementi
    q[n].enqueue(obj);
    tot++;
    ok2get[n].signal();
}


procedur_entry get(int bufnum){
    if (q[n].len == 0){
        ok2get[n].wait();
    }
    tmp = q[n].dequeue();
    tot--;
    ok2add.signal();
    return tmp;
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


monitor cbb {
    condition ok2write; // buffer pieno
    buf buffer of obj_t[MAX];
}

procedur_entry write(obj_t el){
    if (buf.len() == MAX){
        ok2write.wait();
    }
    buf.add(el);
    if (buf.len() < MAX){
        ok2write.signal();
    }
}

procedur_entry int remove(obj_t el){
    int count = 0;
    while (buf.get(el) != NULL){
        count++;
    }
    if (buf.len() < MAX){
        ok2write.signal();
    }
    return count;
}


//es 2
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

void asend (msg_t msg, pid_t dest){
    asend(<getpid(), dest, msg>); //invio messaggio al servizio asincrono
} //servizio asincrono
msg_t arecv (pid_t sender){ //sender può essere ANY 
    while ((msgok = db.get(sender))!= NULL){
        <snd, dst, msg> = abrecv(); //ricevo messaggio dal servizio asincrono
        if (dst == getpid()){
            db.add(snd, msg);
        }
    }
    return msgok;
} 
    

/*
Dato msg passing asincrono, implementare msg passing completamente asincrono.
*/

void casend (msg_t msg, pid_t dest){
    asend(<getpid(), dest, msg>);
} 

void ndrecive (pid_t sender){
    asend (<getpid(), TAG>, getpid()); //mando un messaggio di notifica a me stesso
    while (true){
        <snd, msg> = arecv(ANY);
        if (pid == getpid() && msg == TAG){
            break;
        }
        db.add(<snd, msg>);      
    }
    return db.get(sender); // se non c'è nulla ritorna NULL
}

/*
Dato un msg passing, implementare un msg passing LIFO
*/

void lifosend (msg_t msg, pid_t dest){
    asend(<getpid(), dest, msg>);
} 

msg_t liforeceive (pid_t sender){
    asend (<getpid(), TAG>, getpid()); //mando un messaggio di notifica a me stesso
    while (true){
        <snd, msg> = arecv(ANY);
        if (pid == getpid() && msg == TAG){
            break;
        }
        db.add(<snd, msg>);      
    }
    while (msg = db.getlast(sender) != NULL){ //getlast prende l'ultimo messaggio inserito da sender
        <snd, msg> = areceive(ANY);
        db.add(<snd, msg>);
    }
    return msg;
}



/*
esame 15/01/2020
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
    int value;    // Valore del semaforo
    QueueOfConditions q;    // Coda delle condizioni, una associata ad ogni processo in attesa
    boolean signalReceived = false;        // Per decidere se l'operazione signal è stata effettuata da tick() oppure da V()

    procedure entry void tick() {
        /* Invia ad ogni processo in attesa (in modo non molto elegante, purtoppo, dato che per scorrere la coda rimuove e reinserisce gli elemnti ordinatamente)
        un segnale di "clock": in questo modo si evita di contabilizzare i timer per ogni processo in attesa all'interno del monitor, però si è costretti ad effettuare
        una specie di busy waiting dentro P()... Inoltre, occorre assumere che le istruzioni di questa procedura richiedano
        meno di un millisecondo per essere eseguite (il che può non essere vero se ci sono molti processi in attesa).*/  
        
        int i = 0;
        condition c;
        while(i < q.size()) { // Non uso un ciclo for perché la dimensione di q può cambiare e così il numero di iterazioni  
            c = q.dequeue();
            c.signal();
            if(c != NULL) { // c potrebbe essere stata deallocata se il timer associato è scaduto 
                q.enqueue(c);
            }
            i++;
        }    // Alla fine il front della coda è invariato   
    }
    
    procedure entry void V() {
        if(!q.empty()) {
            signalReceived = true;
            condition c = q.dequeue();
            c.signal();            // Modalità FIFO/fair
            signalReceived = false;    
        }
        else {
            value++;
        }
    }

    procedure entry boolean P(unsigned int timeout) {
        if(value == 0) {
            condition c = new condition();    // Allocata dinamicamente
            q.enqueue(c);
            while(!signalReceived && timeout > 0) { // ~ busy waiting (di dubbia validità) 
                c.wait();
                timeout--;
            }
            free(c);     // c = NULL;
        }
        else {
            value--;
        }
        return (timeout == 0);         
    }
 
    semtimeout(int init) {
        value = init;    
    }

}; 


//Soluzione alternativa:

monitor semtimeout {
    int value;    // Valore del semaforo
    DynArrayQueue q;    // Coda delle condizioni, iterabile come array dinamico
    boolean signalReceived = false;

    procedure entry void tick() {
        iterator i = q.head;
        condition c;
        unsigned int timeout;
        while(i != q.end) { 
            <c, timeout> = *i;
            if(timeout <= 1) {
                c.signal();
            }
            else {
                timeout--;
            }
            i = i->next;
        }
    }
    
    procedure entry void V() {
        if(value == 0) {
            signalReceived = true;
            condition c = q.dequeue();
            c.signal();    
            signalReceived = false;    
        }
        else {
            value++;
        }
    }

    procedure entry boolean P(unsigned int timeout) {
        if(value == 0) {
            condition c = new condition();
            iterator i = q.enqueue(<c, timeout>); // Puntatore all'elemento nella coda
            c.wait();
            q.remove(i);
            free(c); 
        }
        else {
            value--;
        }
        return (!signalReceived);         
    }
 
    semtimeout(int init) {
        value = init;    
    }

}; 


//Esame 05/09/2025
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

#define MAXPASS 100

monitor volo {
    int countcheckin = 0;
    int currentfila ;
    int onboard ;
    condition ok2imbarco[20];  //fila < currentfila
    condition ok2leave; //imbarco completo
}

procedur_entry int checkin(){
    int fila;
    if (countcheckin >= MAXPASS){
        ok2checkin.wait();
    }
    countcheckin++;
    fila = (countcheckin-1)/5 +1; //calcolo della fila
    if (countcheckin < MAXPASS) {
        ok2checkin.signal();
    }
    return fila;
}

procedur_entry void imbarco(int fila){
    /*if (fila < 1 || fila > 20){
        throw "fila non valida";
    }*/
    if (fila < currentfila){
        ok2imbarco[fila].wait();
    }
    ok2imbarco[fila].signal();
    //posso imbarcarmi
}

procedur_entry void a_bordo(){
    onboard++;
    if (onboard == countcheckin){
        ok2leave.signal();
    }
}

procedur_entry void chiama(int fila){
    /*if (fila < 1 || fila > 20){
        throw "fila non valida";
    }*/
    currentfila = fila;
    ok2imbarco[fila].signal();
}

procedur_entry void imbarco_completo(){
    if (onboard < countcheckin){
        ok2leave.wait();
    }
    onboard = 0;
    countcheckin = 0;
    ok2checkin.signal(); //sblocco il checkin per il prossimo volo
}



/*
 Un servizio di message passing asincrono limitato consente di spedire messaggi che contengono un
indentificativo di processo, una flag booleana e un corpo del messaggio di lunghezza <= 1500 byte.
lsend(<pid, flag, body>, dest) // spedisce un messaggio a dest; len(body) <= 1500
<pid, flag, body> = lrecv(sender) // riceve (FIFO) un messaggio da sender (può essere ANY).
Scrivere un servizio di message passing asincrono standard facendo uso di lsend, lrecv.
*/

void ssend(msg_t msg, pid_t dest){
    bool flag;
    for chunk in msg.split(1500){ //suddivido il messaggio in chunk di 1500 byte
        flag = chunk.length() < 1500; //se è l'ultimo chunk imposto la flag a true
        lsend(<getpid(), flag, chunk>, dest);
    }
    msg_t arecv(pid_t sender){
        msg_t msg;
        while (true){
            msg = db.get(sender); //prendo tutti i messaggi arrivati da sender
            if (msg != NULL) return msg;
            <snd, flag, chunk> = lrecv(ANY);
            db.add(<snd, flag, chunk>);
        }
}


//Esame 23/06/2025
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

semaphore mutex(1);
semaphore tlock[](0);
int thr = 0;
int nlock[]; //array dinamico per tenere traccia del numero di processi bloccati per ogni livello

void threshlock(int level){
    mutex.P();
    if (level >= thr){
        nlock[level]++;
        mutex.V();
        tlock[level].P();
        if (nlock[level] > 0){
            tlock[level].V();
        }
        else {
            mutex.V();
        }
    }
    else {
        mutex.V();
    }
    
}


void chthreshold(int newlevel){
    mutex.P();
    thr = newlevel;
    for (int level = thr; level < newlevel; level++){
        while (nlock[level] > 0){
            nlock[level]--;
            tlock[level].V();
        }
    }
    thr = newlevel;
    mutex.V();
}