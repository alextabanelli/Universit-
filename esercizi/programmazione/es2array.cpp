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

bool is_in(int A[], int length, int k){
	
	bool trovato = false ;
	int i = 0 ;
	while (!trovato && (i < length)){
		if (A[i] == k) trovato = true ; else i = i+1 ;
	}
	return (trovato);
}

void print_onlyonce(int A[], int const length){
	
	for (int i = length-1; i >=0; i = i-1){
		//cout << "Cout " << is_in(A, length, A[i]) << ' ' << A[i] << endl ;
		if (is_in(A, i-1, A[i])==false) {	
			cout << A[i] <<' ' ;	
		}
	}
	
}

int main(){
	int const length = 20;
	int A[length];
	initialize(A,length);
	print_array(A,length);
	cout << "Array senza ripetizioni ";	
	print_onlyonce(A,length);
	//cout << is_in(A, length, 12121);
}
