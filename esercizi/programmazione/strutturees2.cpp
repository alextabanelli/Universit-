#include <iostream>
#include <cmath>
#include <ctime>

using namespace std ;
const int length = 29 ;

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

void stampa_lista1(nodo A[]){
    int i = 0 ;
    while (i != -1) {
        cout << A[i].val << ' ' ;
        i = A[i].next ;
    }
    cout << endl ;
}


int get_last( nodo A[]){
    int i = 0 ;
    int res ;
    while (i != -1){
        res = A[i].val ;
        i = A[i].next ;
    }
    return(res) ;
}

void revert(nodo A[]) {
	int temp, i = 0;
	while (A[i].next!=-1){
		temp=A[i].val;
		A[i].val=A[A[i].next].val;
		A[A[i].next].val=temp;
		i = A[i].next;
		i = A[i].next;
		//cout << "I: " << i << endl;
	}
    
}
/*
void remove_last(nodo A[]){
    // ESERCIZIO
}*/

int main(){
    srand(time(0)) ;
    nodo Lista[length] ;
    crea_lista(Lista, length) ;
    stampa_lista1(Lista) ;   
    cout << get_last(Lista) << endl;   
	revert(Lista);
	stampa_lista1(Lista) ;
    return(0) ;
}
