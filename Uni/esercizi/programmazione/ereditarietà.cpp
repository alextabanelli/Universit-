#include <iostream>
#include <ctime>
using namespace std ;

class ContoBanca {
	protected:
		double saldo ;
		
	public:
		void versa(double n) {
			saldo = saldo+n; 
		}
		double preleva(double n) {
			if (n <= saldo){
				saldo = saldo-n;
				return (saldo);
			}
		
		}
		
		int read_saldo(){
			return (saldo);
		}
		ContoBanca() { saldo = 0; }
		ContoBanca(double x ){
			saldo = x;
		}
		
};

class contoInteressi : public contoBanca {
	public:
		void interesse () {
			saldo = saldo*1.02;
		}
		ContoInteressi(double x): ContoBanca(x){
		}
};


int main (){
	contoInteressi A = ContoInteressi(50);
	cout << A.read_saldo() << endl;
	A.interesse();
	cout << A.read_saldo() << endl;
}
