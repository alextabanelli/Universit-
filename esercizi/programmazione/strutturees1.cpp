#include<iostream>
#include<ctime>
using namespace std;

const int length = 29;

struct nodo {
    int val ;
    int next ;
};

void crea_lista(nodo A[], const int length){
    int i ;
    for (i = 0 ; i < length/2 ; i=i+2) {
        A[i].val = rand()%(2*length) ;
        A[i].next = length - i - 1;
        A[length-i-1].val = rand()%(2*length) ;
        A[length-i-1].next = i+2 ;
    }
    // l'ultimo elemento si trova immediatamente dopo il centro...
    if (length%2 == 0) A[i-1].next = -1 ;
    else A[i].next = -1 ;
}

void stampa_lista(nodo A[], const int length){
	int i = 0;
	while (i<length){
		cout << A[i].val << " ";
		if (i==(length/2)-1 && length%2==0){
			i=i+1;
		}
		else i=i+2;
	}
}

void stampa_listatutto(nodo A[], const int length){
	int i = 0;
	while (i<length){
		cout << A[i].val << " ";
		cout << "I: " << i << endl;
		i = i+1;
	}
}

int stampa_lista2(nodo A[]){
	int i = 0, res;
	while (i !=- 1){
		res = A[i].val;
		i = A[i].next;
	}
	return (res);
}


int get_last (nodo A[]){
	int i = 0;
	int res;
	while (i != -1){
		res = A[i].val;
		i = A[i].next;
	}
	return (res);
}
	

int main(){
    srand(time(0)) ;
    nodo Lista[length] ;
    crea_lista(Lista, length) ;
    stampa_listatutto(Lista, length) ;
    cout << endl;
    stampa_lista(Lista, length) ;
    cout << endl;
    cout << stampa_lista2(Lista) ;
    cout << endl;
	cout << "Val: " << get_last (Lista);
    return(0) ;
}
