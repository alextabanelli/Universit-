#include <iostream>
using namespace std;

int main() {
    int m, res , exp;
	cout << "Dammi il numero binario" << endl;
	cin >> m;
	exp = 1;
	res = 0;
	while (m>0){
		res = res + (m%10)*exp;
		exp = exp*2;
		m = m/10;
	}
	cout << res;
    return 0;
}

