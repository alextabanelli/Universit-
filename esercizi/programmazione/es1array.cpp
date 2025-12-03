#include<iostream>

using namespace std;
/*
bool is_in_totheright(int A[], int length, int k, int n){
	
	bool trovato = false ;
	int i = n-1 ;
	while (!trovato && (i < length)){
		if (A[i] == k) trovato = true ; else i = i+1 ;
	}
	
	return (trovato);
}*/

bool is_in(int A[], int length, int k){
	
	bool trovato = false ;
	int i = 0 ;
	while (!trovato && (i < length)){
		if (A[i] == k) trovato = true ; else i = i+1 ;
	}
	return (trovato);
}

int main(){
	int const length = 10;
	int A[length], k, n;
	cout << "Dammi l'array da " << length << "spazi" << endl;
	for (int i = 0; i < length; i = i+1){
		cin >> A[i];
	}
	cout << "Dammi k ";
	cin >> k;
	//cout << "Dammi n ";
	//cin >> n;
	cout << "Il valore k si trova a destra di n: " << is_in(A,length,k);
}
