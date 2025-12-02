#include<iostream>
using namespace std;
/*
for( ;n>1; n=n-1) 
	fattoriale = fattoriale*n;

*/

int fact (int n){
	int fattoriale = 1;
	while(n>1){
            fattoriale = fattoriale*n;
            n = n-1;
        }
        return (fattoriale);
}

int main (){
	int n;
	cout << "Dammi un numero" << endl;
	cin >> n;
	cout << fact (n);
	return (0);
}
