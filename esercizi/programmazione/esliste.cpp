#include <iostream>
#include <ctime>
using namespace std ;

struct lista {
	int val;
	lista *next;
};

typedef lista *plista;

struct listaliste {
	plista head;
	listaliste *next;
};

typedef listaliste *plistaliste;

	//lista *p, *q, *head;

	/*for (int i = 0; i<n; i = i+1){
		//cout << (*head).val << ' ' << (*head).next << endl;
		cout << (*head).val << ' ' ;
		head = (*head).next;
	}*/

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

void print_list2 (plista head){
	bool end = true;
	while (end){
		if ((*head).next==NULL) end = false;
		//cout << head << ' ' << (*head).val << ' ' << (*head).next << endl;
		cout << (*head).val << ' ' ;
		head = (*head).next;
		}
}

void print_liste (plistaliste A){
	bool end = true;
	while (end){
		if ((*A).next==NULL) end = false;
		cout << (*A).head << ' ' << (*A).next << endl;
		//cout << (*head).val << ' ' ;
		A = (*A).next;
		}
}


/*for (int i = 0; i<n; i = i+1){
		(*q).val = rand()%51;
		if (i==n-1) (*q).next = NULL;
		else {
			p = new lista;
			(*q).next = p;
		}q = p;
	}*/

plista new_list (){
	plista p, q, head;
	head = new lista;
	q = head;
	int n;
	cout << "Quanti elementi deva avere la lista?" << endl;
	cin >> n;  // precondition n>0
	for (int i = 0; i<n; i = i+1){
		(*q).val = rand()%51;
		if (i==n-1) (*q).next = NULL;
		else {
			p = new lista;
			(*q).next = p;
		}q = p;
	}
	return (head);
}


void new_and_print (int n){
	cout << "Creazione lista" << ' ' << n << endl;
	print_list(new_list());
}




plista new_liste (){
	bool trovato = true;
	plistaliste p, q, start;
	start = new listaliste;
	q = start;
	int n, x;
	cout << "Quante liste vuoi creare?" << endl;
	cin >> n;  // precondition n>0
	for (int i = 0; i<n; i = i+1){
		(*q).head = new_list();
		if (i==n-1) (*q).next = NULL;
		else {
			p = new listaliste;
			(*q).next = p;
		}q = p;
	}
	//print_liste (start);
	cout << "Quale lista vuoi stampare?" << endl;
	cin >> x;  // precondiiton x<n
	int j=1;
	while (trovato){
		
		if (j==x) trovato = false;
		else {
			start = (*start).next;
			j = j+1;
		}
		
	}
	return ((*start).head);
}



plistaliste new_liste2 (){
	bool trovato = true;
	plista val;
	plistaliste p, q, start;
	start = new listaliste;
	q = start;
	int n, x;
	cout << "Quante liste vuoi creare?" << endl;
	cin >> n;  // precondition n>0
	for (int i = 0; i<n; i = i+1){
		val = new_list();
		(*q).head = val;
		print_list (val);
		if (i==n-1) (*q).next = NULL;
		else {
			p = new listaliste;
			(*q).next = p;
		}q = p;
	}
	return (start);
}





void nliste (){
	int n;
	cout << "Quante liste vuoi creare?"  << endl;
	cin >> n;
	for (int i = 0; i<n; i = i+1){
		new_and_print (i+1);
	} 
}





int sumall (plistaliste A){
	plista val;
	bool end1 = true;
	bool end2;
	int somma = 0;
	while (end1){
		end2 = true;
		if ((*A).next==NULL) end1 = false;
		val = (*A).head;
		while (end2){
		if ((*val).next==NULL) end2 = false;
		somma = somma + (*val).val;
		val = (*val).next;
	}
		A = (*A).next;
	}
	
	return (somma);
}

int main (){
	srand(time(NULL));
	plista val;
	//plista p, q, head;
	//q = head;
	//new_list();
	//print_list(new_list());
	//nliste();
	//new_and_print (1);
	//val = new_liste();
	//cout << sumint(val) << endl;
	//print_list(val);
	cout << "La somma vale " << sumall(new_liste2());
	return (0);
}
