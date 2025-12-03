#include <iostream>
#include <ctime>
using namespace std ;

struct Node {
	int elem;
	Node* next;
};

typedef Node* pnode;

pnode init(pnode& q) {
	q = NULL;
	return (q);
}


void printN(const  pnode s){
	pnode p = s;
	while (p != NULL){
		cout << p->elem << ' ';
		p = p->next;
	}
	cout << endl;
}

void push(pnode q, int elem) {
	pnode pred = q;
	while (q != NULL){
		pred = q;
		q = q->next;
	}
	Node* p = new Node;
	p->elem = elem;
	pred->next = p;
	p->next = NULL;
}

pnode crea_pnode(pnode& q){
	for (int i = 0; i <10; i = i+1) push(q, rand()%21);
}

/*void pop_tail(listn& q) {
	Node* p = q.head;
	Node* m = q.head;
	while (p->next != NULL){
		m = p;
		p = p->next;
	}
	q.tail = m;
	q.tail->next = NULL;
}*/


/*void iniz_pal(listn& l, int n){
	init(l);
	push_head(l, 0);
	for (int i = 0; i<n/2; i = i+1){
		int m = rand()%20;
		push_head(l, m);
		push_tail(l, m);
	}
}*/

int min_list(const  pnode p){
	pnode q = p;
	if (q == NULL) return (-1);
	else if (q->next = NULL) return (q->elem);
	else {
		if (q->elem < min_list(q->next)) return (q->elem);
		else return (min_list(q->next));
	}
}


int main (){
	srand(time(NULL));
	pnode a;
	init(a);
	printN(crea_pnode(a));
	min_list(a);
}
