#include <iostream>
#include <ctime>
using namespace std ;

int radice_quadrata(int n){
	int x = 1;
	while (x*x<= n) x = x+1;
	return (x-1);
}


int radice_quadrata_ric(int n, int x){
	if (x*x<= n) return (radice_quadrata_ric(n, x+1));
	else return (x-1);
}

int main (){
	cout << radice_quadrata(54) << ' ' << radice_quadrata_ric(54,1);
}
