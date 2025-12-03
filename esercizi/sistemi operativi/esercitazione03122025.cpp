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


