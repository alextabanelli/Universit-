#include<iostream>
#include<cmath>
using namespace std;

void soluzioni( double a, double b, double c, double &sol1, double &sol2){
	double tmp = sqrt(b*b - 4*a*c);
	sol1 = (-b-tmp)/2*a;
	sol2 = (-b+tmp)/2*a;
	
}

int main (){
	double x1, x2;
	soluzioni (1, 0, -1, x1, x2);
	cout << x1 << " "<< x2;
	return(0);
}
