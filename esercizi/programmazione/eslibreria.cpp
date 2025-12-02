#include <iostream>
#include "funzioni.h"
using namespace std;
//using namespece funzioni;

int main (){
	int a, b;
	cout << "Danni a" << endl;
	cin >> a;
	cout << "Danni b" << endl;
	cin >> b;
	cout << "A vale " << bin2dec(a) << endl;
	cout << "B vale " << bin2dec(b) << endl;
	cout << "Somma vale " << bin_sum(a,b) << endl;
	cout << "Prodotto vale " << bin_prod(a,b) << endl;

}
