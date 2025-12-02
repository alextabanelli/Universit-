#include<iostream>
#include<ctime>
using namespace std;

void initialize(int A[], const int length){
    srand( time(0) ) ;
    for (int i = 0; i < length ; i=i+1)
        A[i] = rand()%(3*length +1) ;
}

void print_array(int A[], const int length){
    for (int i = 0; i < length ; i=i+1)
        cout << A[i] << ' ' ;
    cout << endl ;
}

int secoccur (int A[], const int length){
	bool trovato = true;
	int i = 0, j;
	while (i<length && trovato){
		j=i+1;
		while (j<length && trovato){
			if (A[i]==A[j]) trovato=false;
			else j=j+1;
		}
		i=i+1;
	}
	if (trovato) return(-1);
	else return (j);
}

int main (){
	const int length = 20;
	int A[length];// = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	initialize(A,length);
	print_array(A,length);
	cout << "Risultato seconda occorrenza :" << secoccur(A,length);
	return 0;
	
}
