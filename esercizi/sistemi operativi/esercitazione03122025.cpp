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
    mutex.V();
}


//Esame 20/01/2023
/*
 Scrivere il monitor fullbuf che abbia le seguenti procedure entry:
void add(int value)
int get(void)
Le prime MAX chiamate della procedure entry add devono bloccare i processi chiamanti. In seguito deve sempre valere
Na >= MAX indicando con Na il numero di processi bloccati in attesa di completare la funzione add.
La funzione get deve attendere che Na > MAX, restituire la somma algebrica dei parametri value delle chiamate add in
sospeso e riattivare il primo processo in attesa di completare la add (se la get richiede che Na > MAX, la get può
riattivare un processo e al completamento della get si rimarrà garantito che Na >= MAX)

*/

monitor fullbuf {
    int na = 0; //numero di processi bloccati in add
    int sum = 0; //somma dei valori passati a add
    condition ok2add; //per add, totn >= MAX
    condition ok2get; //per get, totn > MAX
}

procedur_entry void add(int value){
    na++;
    sum += value;
    if (na > MAX){
        ok2get.signal();
    }
    ok2add.wait();
    sum -= value;
    na--;

}

procedur_entry int get(void){
    //int rv;
    if (na <= MAX){
        ok2get.wait();
    }
    //rv = sum; se si vuole restituire la somma, con anche il processo che viene sbloccato
    ok2add.signal();
    return sum;
    //return rv;
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
    queue of condition qf; //Queue FIFO
    stack of condition sl; // Stack LIFO
    condition ok2get; //wf == 0 || wl == 0
    int wg, sum; //numero di getboth in attesa
}

procedur_entry void addfirst(int val){
    condition c;
    qf.enqueue(c);
    if (wg > 0 && sl.len() > 0){
        ok2get.signal();
    }
    else {
        c.wait();
        sum += val;
    }
}


procedur_entry void addlast(int val){
    condition c;
    sl.push(c);
    if (wg > 0 && qf.len() > 0){
        ok2get.signal();
    }
    else {
        c.wait();
        sum += val;
    }
}
procedur_entry int getboth(void){
    sum = 0;
    if (qf.len() == 0 || sl.len() == 0){
        wg++;
        ok2get.wait();
        wg--;
    }
    signal(qf.dequeue());
    signal(sl.pop());
    return sum;
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


void altsend(msg_t msg, pid_t destination){
    asend(<getpid(), msg>, destination);
}

msg_t altrecv(pid_t sender){
    static last = 0; //variabile statica per alternare tra primo e ultimo
    asend(<getpid(), TAG>, getpid()); //mando un messaggio di notifica a me stesso
    while (true){
        <snd, msg> = arecv(ANY);
        if (snd == getpid() && msg == TAG){
            break;
        }
        db.add(<snd, msg>);
    }
    while (true){
        msg = db.get(sender, last); //getalt alterna tra il primo e l'ultimo messaggio di sender
        if (msg != NULL){ //se ho trovato un messaggio lo ritorno
            last = 1 - last; //alterno il valore di last
            return msg;
        }
        <snd, msg> = arecv(ANY);
        db.add(<snd, msg>);
    }
}


//Esame 29/05/2024

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

monitor urgentsem {
    int value; //valore del semaforo
    condition cp; //per P
    condition cup; //per UP
}

 void init(int initvalue){
    value = initvalue;
}

procedur_entry void P(void){
    if (value == 0){
        cp.wait();
    }
        value--;
}

procedur_entry void UP(void){
    if (value == 0){
        cup.wait();
    }
        value--;
}

procedur_entry void V(void){
    value++;
    cup.signal();
    if (value > 0){
        cp.signal();
    }
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


semaphore mutex;
semaphore keywait; //dizionario di array dinamici di condizioni
semaphore cont;
int oldkey;
int nw = 0; //numero di processi in attesa
int nproc = 0; //numero di processi totali


int syncvalue(int key){
    int rv;
    mutex.P();
    if (key != oldkey){
        if (nw > 0){
            nproc = nw;
            keywait.V();
            cont.P();
        }
    }
    oldkey = key;
    nw++;
    mutex.V();
    keywait.P();
    nw--;
    rv = nproc;
    if (nw == 0){
        cont.V();
    }
    else {
        keywait.V();
    }
    return rv;
}


//Esame 13/02/2024

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


monitor rgbsum {
    #define red 0
    #define green 1
    #define blue 2
    int currentcolor; //colore corrente
    condition ok2go; //color != currentcolor
    int sum; //somma dei valori
}

procedur_entry double rgb(int color, double value){
    if (color != currentcolor){
        ok2go.signal();
        sum = 0;
    }
    currentcolor = color;
    sum += value;
    ok2go.wait();
    ok2go.signal();
    return sum;
}


/*
 Sia dato un sistema di message passing asincrono con duplicazione dei messaggi.
dsnd(msg_t msg, pid_t dest)
msg_t drecv(pid_t sender)
I messaggi spediti con dsend verranno sicuramente ricevuti almeno una volta ma possono essere ricevuti più volte. È
garantita la consegna FIFO.
Implementare un sistema di message passing asincrono (classico). (non fare uso di processi server)
*/


last[]; //array dinamico per tenere traccia dell'ultimo contatore per ogni mittente, se si accede a last[snd] non inizializzato si assume che valga 0
cnt = 0; //contatore globale dei messaggi inviati

asnd(msg_t msg, pid_t dest){
    cnt++;
    dsnd(<getpid(),cnt, msg>, dest);
}

msg_t arecv(pid_t sender){
    while (true){
        <snd, cnt, msg> = drecv(sender);
        if (last[snd] < cnt){
            last[snd] = cnt;
            break;
        }
    return msg;  
    }
}



//Esame 17/01/2024


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
    char buf;
    condition ok2send; //per sendchar
    condition ok2recv; //per recvchar
    condition ok2add; //buffer pieno
    condition ok2get; //buffer vuoto
    bool full = false; //indica se il buffer ha un dato
    bool senderbusy; //indica se c'è un sender attivo
    bool receiverbusy; //indica se c'è un receiver attivo
}

procedur_entry void startsend(void){
    if (senderbusy){
        ok2send.wait();
    }
    senderbusy = true;
}

procedur_entry void sendchar(char c){
    if (full){
        ok2add.wait();
    }
    buf = c;
    full = true;
    ok2get.signal();
    if (c == 0){
        senderbusy = false;
        ok2send.signal();
    }  
}

procedur_entry void startrecv(void){
    if (receiverbusy){
        ok2recv.wait();
    }
    receiverbusy = true;
}

procedur_entry char recvchar(void){
    char rv;
    if (!full){
        ok2get.wait();
    }
    rv = buf;
    full = false;
    ok2add.signal();
    if (rv == 0){
        receiverbusy = false;
        ok2recv.signal();
    }
    return rv;
}