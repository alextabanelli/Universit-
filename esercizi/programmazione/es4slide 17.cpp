#include <iostream>
using namespace std;
int n;
int main(){
	int i, esp = 10, z;
	cout << "Dammi n" << endl;
	cin >> n;
	while (n>0){
		z = n%esp;
		cout << z;
		n = n/esp;
	}
}
