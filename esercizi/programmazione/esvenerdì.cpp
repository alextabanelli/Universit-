#include <iostream>
#include <ctime>

using namespace std;


int const MAX = 1024; 

typedef int Ptr; //pointer o puntatore

struct Node {
	int elem;
	Ptr next;
};

struct list {
	Node node[MAX];
	Ptr head;
	Ptr free;
};

void iniz (list& l){
	l.head = -1;
	l.free = 0;
	for (int i = 0; i<MAX-1; i = i+1){
		l.node[i].next = i+1;
		l.node[MAX-1].next = -1;
	}
}

void print (list l){
	cout << "Stampo lista L" << endl;
	while (l.head != -1){
		cout << l.node[l.head].elem << ' ';
		l.head = l.node[l.head].next;
	}
	cout << endl;
}

Ptr alloc (list& l, int elem, Ptr next){
	const Ptr p = l.free;
	if (p == -1){
		cerr << "Out of memory" << endl;
		return (-1);
	
	}
	else {
		l.free = l.node[p].next;
		l.node[p].elem = elem;
		l.node[p].next = next;
		return (p);	
	}
	

}

void free (list& l, const Ptr p){
	if (p != -1){
		l.node[p].next = l.free;
		l.free = p;
	}
	else cerr << "Invalid pointer" << endl;
}

void push_front (list& l, int elem){
	const Ptr p = alloc(l, elem, l.head);
	if (p != -1) l.head = p;
}

void pop_front (list& l){
	if (l.head != -1) {
		const Ptr p = l.head;
		l.head = l.node[p].next;
		free (l, p);
	}
}


void push_back (list& l, int elem){
	Ptr p = l.head;
	while (p != -1 && l.node[p].next != -1){
		p = l.node[p].next;
	}
	if (p == -1){
		push_front(l, elem);
	}
	else {
		const Ptr q = alloc(l, elem, -1);
		if (q != -1) l.node[p].next = q;	
	}

}

void pop_back (list& l){
	Ptr p = l.head;
	Ptr prev = -1;
	while (p != -1 && l.node[p].next != -1){
		prev = p;
		p = l.node[p].next;
	}
	if (p != -1){
		if (prev == -1) l.head = -1;
		else l.node[prev].next = -1;
		free (l, p);	
	}
}

void reverse (list& l){
	Ptr p = l.head;
	Ptr r = -1;
	while (p != -1){
		const Ptr q = l.node[p].next;
		l.node[p].next = r;
		r = q;
		p = q;
	}
	l.head = r;
}

int length(const list& l){
	int length = 0;
	Ptr e = l.head;
	while (e != -1){
		length = length+1;
		e = l.node[e].next;
	}
	return (length);
}

int sum(const list& l){
	int sum = 0;
	Ptr e = l.head;
	while (e != -1){
		sum = sum+l.node[e].elem;
		e = l.node[e].next;
	}
	return (sum);
}


int find_min(const list& l){
	int min = -1;
	Ptr e = l.head;
	if (e != -1){
		min = l.node[e].elem;
		while (e != -1){
			if (l.node[e].elem<min) min = l.node[e].elem;
			e = l.node[e].next;
		}	
	}
	return (min);
}

float average(const list& l) {
	return (sum(l)/length(l));
}

bool member(const list& l, int elem){
	bool trovato = false;
	Ptr e = l.head;
	while (e != -1 && !trovato){
		if (l.node[e].elem==elem) trovato = true;
		e = l.node[e].next;
	}
	return (trovato);
}

void ordina(list& l){
	Ptr e = l.head;
	int i = l.head;
	int min, tmp, emin;
	while (i != -1){
		min = l.node[i].elem;
		emin = i;
		e = i;
		while (e != -1){
			if (l.node[e].elem < min){
				min = l.node[e].elem;
				emin = e;
			}
			e = l.node[e].next;
		}
		tmp = l.node[i].elem;
		l.node[i].elem = min;
		l.node[emin].elem = tmp;
		i = l.node[i].next;
	}
}

void insert(list& l, int elem){
	push_front(l, elem);
	ordina (l);
} 

void copy_list(list l, list& m){
	m.head = l.head;
	while (l.head != -1){
		m.node[l.head].elem = l.node[l.head].elem;
		m.node[l.head].next = l.node[l.head].next;
		l.head = l.node[l.head].next;
	}
}

void sort(const list& l, list& m){
	copy_list(l,m);
	ordina(m);
}

void remove(list& l, int elem){
	Ptr e = l.head, preve;
	bool trovato = true;
	if (length(l)==0) cerr << "Lista vuota" << endl;
	else if (l.node[e].elem == elem) pop_front(l);
	else if (l.node[e].next != -1) {
		preve = e;
		e = l.node[e].next;
		while (e != -1 && trovato){
			if (l.node[e].elem == elem){
				if (l.node[e].next == -1) pop_back(l);
				else {
					l.node[preve].next = l.node[e].next;
					free (l,e);
				}
				trovato = false;
			}
			else {
				preve = e;
				e = l.node[e].next;	
			}		
		}
	}	
}



int main (){
	srand(time(NULL));
	cout << "Entro nel main" << endl;
	struct list lista, lista2;
	iniz (lista);
	for (int i = 0; i<0; i = i+1){
		push_front (lista, rand()%51);
	}
	print (lista);
	cout << "Length :" << length(lista) << endl;
	cout << "Somma :" << sum(lista) << endl;
	//cout << "Media :" << average(lista) << endl;
	cout << "Min :" << find_min(lista) << endl;
	cout << "37 fa parte: " << member(lista, 37) << endl;
	insert(lista, 37);
	print(lista);
	sort(lista, lista2);
	cout << "Lista 2:";
	print(lista2);
	cout << endl;
	remove (lista, 37);
	cout << "Lista senza la prima occorrenza di 37" << endl;
	print (lista);
}
