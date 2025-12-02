#include <iostream>
#include <ctime>
using namespace std ;


struct lista {
	int val;
	lista *next;
};

typedef lista *plista;

void print_list (plista head){
	bool end = true;
	while (end){
		if ((*head).next==NULL) end = false;
		//cout << (*head).val << ' ' << (*head).next << endl;
		cout << (*head).val << ' ' ;
		head = (*head).next;
		}
		cout << endl;
}

int x = 0;

plista crea_lista (int n){
	if (n > 0){
		plista h = new lista;
		h->val = x;
		x = x+1;
		h->next = crea_lista (n-1);
		return (h);	
	}
	else return (NULL);
}

void write_vertical(int n) {
	if (n <= 9) cout << n << endl;
	else { write_vertical (n/10) ;
		cout << n%10 << endl ;
	}
}

void write_vertical2(int n) {
	if (n <= 9) cout << n << endl;
	else { cout << n%10 << endl ;
		write_vertical2 (n/10);	
	}
}



void aste(int n) {
	if (n == 1) cout << '*' << ' ';
	else { aste (n-1) ;
		cout << '*' << ' ';
	}
}

void aste2(int n) {
	if (n > 0) {
		aste2 (n-1) ;
		//cout << n << ' ';
		for (int i = 0; i < n*n; i = i+1){
			cout << '*' << ' ' ;
		}
	}
}



int main (){
	aste2(5);
	//print_list (crea_lista(10));
}
