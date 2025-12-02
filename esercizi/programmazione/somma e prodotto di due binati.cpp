#include <iostream>
using namespace std;
/*
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

int main (){
	int a, b, somma, prodotto;
	cout << "Dammi a" << endl;
	cin >> a;
	cout << "Dammi b" << endl;
	cin >> b;
	somma = bin2dec(a)+bin2dec(b);
	prodotto = bin2dec(a)*bin2dec(b);
	cout << "Somma vale " << dec2bin(somma)<< " " << somma <<  endl;
	cout << "Prodotto vale " << dec2bin(prodotto) << " " << prodotto;
}
*/

int x, y; //variabili globali
void bin2dec(){
	int m, res , exp;
	//cout << "Dammi il numero binario" << endl;
	//cin >> m;
	m = x;
	exp = 1;
	res = 0;
	while (m>0){
		res = res + (m%10)*exp;
		exp = exp*2;
		m = m/10;
	}
	y = res;
}

void dec2bin(){
	int m, res , exp;
	//cout << "Dammi il numero binario" << endl;
	//cin >> m;
	m = x;
	exp = 1;
	res = 0;
	while (m>0){
		res = res + (m%2)*exp;
		exp = exp*10;
		m = m/2;
	}
	y = res;
}

int main (){
	int res1, res2;
	int somma, prodotto;
	cin >> x;
	y = 0;
	bin2dec();
	res1 = y;
	cin >> x;
	y = 0;
	bin2dec();
	res2 = y;
	somma = res1+res2;
	prodotto = res1*res2;
	x = somma;
	y = 0;
	dec2bin();
	cout << "Somma vale " << y << endl;
	x = prodotto;
	y = 0;
	dec2bin();
	cout << "Prodotto vale " << y << endl;
}


