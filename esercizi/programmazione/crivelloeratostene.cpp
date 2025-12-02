#include <iostream>
#include <ctime>

using namespace std;

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



plista new_list (int n){
	plista p, q, head;
	head = new lista;
	q = head;
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

plista new_listo (int n){
	plista p, q, head;
	head = new lista;
	q = head;
	for (int i = 0; i<n; i = i+1){
		(*q).val = i;
		if (i==n-1) (*q).next = NULL;
		else {
			p = new lista;
			(*q).next = p;
		}q = p;
	}
	return (head);
}



plista remove_first (plista head, int e){
	plista p, p_before;
	p = head;
	p_before = head;
	while ((p != NULL) && (p->val != e)){
		p_before = p;
		p = (*p).next;
	}
	if (p == NULL) return(head);
	else if (p == p_before) {
		delete p;
		return((*head).next);
	}
	else {
		(*p_before).next = (*p).next;
		delete p;
		return(head);
	}
}


/*
void remove(plista head, int elem){
	plista p = head;
	plista preve = head;
	if (p == NULL) cerr << "Lista vuota" << endl;
	else if (((p->val)%elem) == 0 && p->next == NULL) {
		p = NULL;
	} else {
		while (p != NULL){
			if (((p->val)%elem) == 0){
				if (p->next == NULL) {
					preve->next = NULL;
					delete p;
				}
				/*else {
					preve = p->next;
					delete p;
					p = preve;
			}
			else {
				preve = p;
				p = p->next;
			}		
			}
		}
	}
			
}
*/


plista remove(plista head, int elem){
	plista p = head;
	plista preve = head;
	while ( p != NULL){
		if ((p->val)%elem == 0){
			if ( p == preve){
				p = p->next;
				delete preve;
				preve = p;
				head = p;
			} else {
				preve->next = p->next;
				delete p;
				p = preve->next;
			}
		} else {
			preve = p;
			p = p->next;
		}
	}
	return (head);		
}


plista remove_cf(plista head, int e){
	plista p = head;
	while (p != NULL){
		if ((p->val)%e == 0){
			head = remove_first(head, p->val);
			p = head;
		} else p = p->next;
	}
	return (head);
}

plista eratostene(plista h){
	plista p = h;
	while (p != NULL){
		p->next = remove_cf(p->next, p->val);
		p = p->next;
	}
	return (h);
}




int main (){
	srand(time(NULL));
	plista h = NULL;
	h = new_list(20);
	print_list(h);
	//print_list(remove_cf(h, 2));
	print_list(new_listo(1000));
	print_list(eratostene(new_listo(1000)));
	return (0);
}


