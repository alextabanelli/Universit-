#include <iostream>
#include "funzioni.h"
using namespace std;


int bin2dec(int m){
	int res , exp;
	//cout << "Dammi il numero binario" << endl;
	//cin >> m;
	exp = 1;
	res = 0;
	while (m>0){
		res = res + (m%10)*exp;
		exp = exp*2;
		m = m/10;
	}
	return(res);
}


int dec2bin(int m){
	int res , exp;
	//cout << "Dammi il numero binario" << endl;
	//cin >> m;
	exp = 1;
	res = 0;
	while (m>0){
		res = res + (m%2)*exp;
		exp = exp*10;
		m = m/2;
	}
	return(res);
}

int bin_sum (int a, int b){
	int somma;
	/*cout << "Dammi a" << endl;
	cin >> a;
	cout << "Dammi b" << endl;
	cin >> b;
	*/
	somma = bin2dec(a)+bin2dec(b);
	return (somma);
	//cout << "Somma vale " << dec2bin(somma)<< " " << somma <<  endl;
}

int bin_prod (int a, int b){
	int prodotto;
	/*cout << "Dammi a" << endl;
	cin >> a;
	cout << "Dammi b" << endl;
	cin >> b;
	*/
	prodotto = bin2dec(a)*bin2dec(b);
	return(prodotto);
	//cout << "Prodotto vale " << dec2bin(prodotto) << " " << prodotto;
}

