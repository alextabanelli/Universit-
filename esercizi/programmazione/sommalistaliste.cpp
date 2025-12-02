/*
NOME: Alex
COGNOME: Tabanelli
Matricola 0001164359
*/

#include <iostream>
#include <ctime>
using namespace std ;

struct lista {
	int val;
	lista *next;
};

typedef lista *plista;

//creazione della lista di liste

struct listaliste {
	plista head;
	listaliste *next;
};

typedef listaliste *plistaliste;


void print_list (plista head){
	bool end = true;
	while (end){
		if ((*head).next==NULL) end = false;
		cout << (*head).val << ' ' ;
		head = (*head).next;
		}
		cout << endl;
}


plista rnew_list (){
	plista p, q, head;
	head = new lista;
	q = head;
	int n;
	n = rand()%5+1; //numero degli elementi randomica da 1 a 5
	for (int i = 0; i<n; i = i+1){
		(*q).val = rand()%51;  //numero randomico da 0 a 50
		if (i==n-1) (*q).next = NULL;
		else {
			p = new lista;
			(*q).next = p;
		}q = p;
	}
	return (head);
}


plistaliste rnew_liste2 (){
	bool trovato = true;
	plista val;
	plistaliste p, q, start;
	start = new listaliste;
	q = start;
	int n, x;
	n = rand()%5+1; //numero delle liste create randomico da 1 a 5
	cout << "Liste create" << ' ' << n << endl;
	for (int i = 0; i<n; i = i+1){
		val = rnew_list();
		(*q).head = val;
		cout << "Lista" << ' ' << i << ": ";
		print_list (val);
		if (i==n-1) (*q).next = NULL;
		else {
			p = new listaliste;
			(*q).next = p;
		}q = p;
	}
	return (start);
}




int sumall (plistaliste A){
	plista val;
	bool end1 = true;
	bool end2;
	int somma = 0;
	while (end1){     //ciclo per entrare nelle liste
		end2 = true;
		if ((*A).next==NULL) end1 = false;
		val = (*A).head;
		while (end2){  //ciclo per sommare gli elementi della lista
		if ((*val).next==NULL) end2 = false;
		somma = somma + (*val).val;
		val = (*val).next;
	}
		A = (*A).next;
	}
	
	return (somma);
}

int main (){
	srand(time(NULL));
	cout << "La somma vale " << sumall(rnew_liste2());
	return (0);
}
