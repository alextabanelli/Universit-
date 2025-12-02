/*#include <iostream>

#include <ctime>

using namespace std ;

const int MAX = 1024;

void push(int A[], int& size, int elem){
	
	if (size==MAX) {
		cout << "Push su pila piena";
	}else {
		A[size] = elem;
		size = size+1;
	}
}

void pop(int A[], int& size){
	
	if (size==0) {
		cout << "Pop su pila vuota";
		
	}else {
		size=size-1;
	}
}

int top(int A[], int size){
	
	if (size==0) {
		cout << "Top su pila vuota";
		return (-1);
	}else return (A[size-1]);

}

void print_stack(int A[], int size){
	cout << "[";
	for (int i=0; i<size;i=i+1){
		cout << " " << A[i];
	} cout << "]" << endl;
}

int main (){
	
	int A[MAX];
	int size = 0; //dimensione della pila
	print_stack(A, size);
	for (int i = 0; i<10; i=i+1){
		push(A, size, i);
	}
		
	print_stack(A, size);
	for (int i = 0; i<5; i=i+1)
		pop(A, size, i);
	print_stack(A, size);
	
}


*/
/*
#include <iostream>

#include <ctime>

using namespace std ;

const int MAX = 1024;

struct Stack {
	int data[MAX];
	int size; // numero di elementi nella pila
};

void init1(struct Stack& A) {
	for (int i=0; i<MAX;i=i+1){
		A.data[i]=0;
	} 
	A.size = 0;
}

void push(struct Stack& A, int elem){
	if (A.size==MAX) {
		cout << "Push su pila piena";
	}else {
		A.data[A.size] = elem;
		A.size = A.size+1;
	}
}

void pop(struct Stack& A){
	
	if (A.size==0) {
		cout << "Pop su pila vuota";
		
	}else {
		A.size=A.size-1;
	}
}

int top(struct Stack& A){
	
	if (A.size==0) {
		cout << "Top su pila vuota";
		return (-1);
	}else return (A.data[A.size-1]);

}

void print_stack(struct Stack A){
	cout << "[";
	for (int i=0; i<A.size;i=i+1){
		cout << " " << A.data[i];
	} cout << "]" << endl;
}

int main (){
	
	struct Stack pila;
	init1(pila);
	pila.size=10;
	print_stack(pila);
	pila.size=0;
	for (int i = 0; i<10; i=i+1){
		push(pila, i);
	}	
	print_stack(pila);
	for (int i = 0; i<5; i=i+1)
		pop(pila);
	print_stack(pila);
	
}

*/
/*
#include <iostream>

#include <ctime>

using namespace std ;

const int MAX = 1024;

struct Stack {
	int data[MAX];
	int size; // numero di elementi nella pila
};

void init1(struct Stack& A) {
	for (int i=0; i<MAX;i=i+1){
		A.data[i]=0;
	} 
	A.size = 0;
}

void push(struct Stack& A, int elem){
	if (A.size==MAX) {
		cout << "Push su pila piena";
	}else {
		A.data[A.size] = elem;
		A.size = A.size+1;
	}
}

void pop(struct Stack& A){
	
	if (A.size==0) {
		cout << "Pop su pila vuota";
		
	}else {
		A.size=A.size-1;
	}
}

int top(struct Stack& A){
	
	if (A.size==0) {
		cout << "Top su pila vuota";
		return (-1);
	}else return (A.data[A.size-1]);

}

void print_stack(struct Stack A){
	cout << "[";
	for (int i=0; i<A.size;i=i+1){
		cout << " " << A.data[i];
	} cout << "]" << endl;
}

void som (struct Stack& A){
	
	A.data[A.size-2]=A.data[A.size-2]+A.data[A.size-1];
	pop(A);
	
}

void dif (struct Stack& A){
	
	A.data[A.size-2]=A.data[A.size-1]+A.data[A.size-2];
	pop(A);
	
}

void prod (struct Stack& A){
	
	A.data[A.size-2]=A.data[A.size-2]*A.data[A.size-1];
	pop(A);
	
}

void div (struct Stack& A){
	if (A.data[A.size-1]==0) cerr << "Divisione per 0";
	else {
		A.data[A.size-2]=A.data[A.size-2]/A.data[A.size-1];
		pop(A);
	}
	
}

int main (){
	bool trovato = true;
	char x;
	struct Stack pila;
	init1(pila);
	print_stack(pila);
	while (trovato){
		cin >> x;
		if (x=='.') trovato = false;
		else if (x>=48 && x<=57) push (pila, (int (x)-48));
		else if (x=='+') som (pila);
		else if (x=='-') dif (pila);
		else if (x=='*') prod (pila);
		else if (x=='/') div (pila);
		else cerr << "Input non valido";
		print_stack(pila);	
	}
	cout << "Fine esecuzione";
	
	
}*/
#include <iostream>


using namespace std ;

const int MAX = 1024;

struct Queue {
	int data[MAX];
	int head; // indice del primo elemento della coda
	int size; // numero di elementi nella coda
};

/* init(q) inizializza la coda q in modo che sia una coda vuota.
• empty(q) restituisce true se la coda è vuota, false altrimenti.
• full(q) restituisce true se la coda è piena, false altrimenti.
• front(q) restituisce il primo elemento della coda (senza rimuoverlo). La
funzione stampa un messaggio di errore se la coda è vuota.
• back(q) restituisce l’ultimo elemento della coda. La funzione stampa un
messaggio di errore se la coda è vuota.
• enqueue(q, elem) inserisce elem in ultima posizione nella coda. La
funzione stampa un messaggio di errore se la coda è piena.
• dequeue(q) rimuove il primo elemento della coda. La funzione stampa un
messaggio di errore se la coda è vuota.
• print_queue(q) stampa gli elementi della coda dal primo all’ultimo.*/


void init1(struct Queue& A) {
	for (int i=0; i<MAX;i=i+1){
		A.data[i]=0;
	} 
	A.size = 0;
	A.head = 0;
}

bool empty(struct Queue& A) {
	bool ret;
	if (A.size==0) ret = true;
	else ret = false;
	return (ret);
}

bool full(struct Queue& A) {
	bool ret;
	if (A.size==MAX) ret = true;
	else ret = false;
	return (ret);
}

int front(struct Queue& A) {
	if (A.size==0) {
		cerr << "Coda vuota" << endl;
		return (-1);
	}
	else return(A.data[A.head]);
}

int back(struct Queue& A) {
	if (A.size==0) {
		cerr << "Coda vuota" << endl;
		return (-1);
	}
	else return(A.data[A.size-1]);
}


void enqueue(struct Queue& A, int elem){
	if (A.size==MAX) {
		cerr << "Coda piena" << endl;
	}else {
		A.data[A.size] = elem;
		A.size = A.size+1;
	}
}

void dequeue(struct Queue& A){
	int i = 0;
	if (A.size==0) {
		cerr << "Coda vuota" << endl;
	}else {
		while (i<A.size-1){
		A.data[i] = A.data[i+1];	
			
			i=i+1;
		}
		
		A.size = A.size-1;
	}
}


void print_queue(struct Queue& A){
	cout << "[";
	for (int i=0; i<A.size;i=i+1){
		cout << " " << A.data[i];
	} cout << "]" << endl;
}



int main (){
	bool trovato = true;
	char x;
	int elem;
	struct Queue coda;
	init1(coda);
	print_queue(coda);
	cout << "Menu della coda" << endl;
	cout << "Comandi" << endl;
	cout << "Premere [1] per fare empty" << endl;
	cout << "Premere [2] per fare full" << endl;
	cout << "Premere [3] per fare front" << endl;
	cout << "Premere [4] per fare back" << endl;
	cout << "Premere [5] per fare enqueue" << endl;
	cout << "Premere [6] per fare dequeue" << endl;
	cout << "Premere [.] per terminare il programma" << endl;
	while (trovato){
		cin >> x;
		if (x=='.') trovato = false;
		else if (x=='1') cout << empty(coda);
		else if (x=='2') cout << full(coda);
		else if (x=='3') cout << front(coda);
		else if (x=='4') cout << back(coda);
		else if (x=='5') {
			cout << "Dammi l'elemento da inserire nella pila" << endl;
			cin >> elem;
			enqueue(coda, elem);
		}
		else if (x=='6') {
			dequeue(coda);
		}
		else cerr << "Input non valido" << endl;
		print_queue(coda);	
	}
	cout << "Fine esecuzione";
	
	
}





