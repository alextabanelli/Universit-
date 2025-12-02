#include<iostream>
using namespace std;

int isprime (int n){
	bool con = true;
	int m = 2;
	while(m<n && con){
		    if (n%m==0) con = false;
            m = m+1;
        } 
        return (con);
}

int main (){
	int n;
	cout << "Dammi un numero" << endl;
	cin >> n;
	cout << isprime (n);
	return (0);
}
