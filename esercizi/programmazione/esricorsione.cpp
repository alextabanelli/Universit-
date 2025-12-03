#include <iostream>
#include <ctime>
using namespace std ;


struct Node {
	int elem;
	Node* next;
};


struct listn {
	Node* head; 
	Node* tail; 
};


void init(listn& q) {
	q.head = NULL;
	q.tail = NULL;
}


void printL(const  listn s){
	Node* p = s.head;
	while (p != NULL){
		cout << p->elem << ' ';
		p = p->next;
	}
	cout << endl;
}

void push_tail(listn& q, int elem) {
	Node* p = new Node;
	p->elem = elem;
	p->next = NULL;
	if (q.head == NULL) {
		q.tail = p;
		q.head = q.tail;	
	} else {
		q.tail->next = p;
		q.tail = p;
	}	
}

void pop_tail(listn& q) {
	Node* p = q.head;
	Node* m = q.head;
	while (p->next != NULL){
		m = p;
		p = p->next;
	}
	q.tail = m;
	q.tail->next = NULL;
}

void push_head(listn& q, int elem) {
	Node* p = new Node;
	p->elem = elem;
	p->next = NULL;
	if (q.head == NULL) {
		q.tail = p;
		q.head = q.tail;	
	} else {
		p->next = q.head;
		q.head = p;
	}	
}

void iniz_pal(listn& l, int n){
	init(l);
	push_head(l, 0);
	for (int i = 0; i<n/2; i = i+1){
		int m = rand()%20;
		push_head(l, m);
		push_tail(l, m);
	}
}



int sum (int a, int b){
	if (b==0) return (a);
	else return ( (sum(a, b-1))+1 );
}


int prod (int a, int b){
	if (b==0) return (0);
	else if (b==1) return (a);
	else return ( (prod(a, b-1))+a);
}

int sum_arr (int A[], int length){
	if (length == 0) return (0);
	else return ((sum_arr(A,length-1))+A[length-1]);
}

int sqrt_int (int n){
	if (n == 0) return (0);
	else if (n == 1) return (1);
	else return (0);
}


bool pal (listn A){
	if (((A.head->elem) == (A.tail->elem)) && (A.head->elem == 0)) return (true);
	else {
		bool eq;
		if (A.head->elem == A.tail->elem) eq = true;
		else eq = false;
		A.head = A.head->next;
		pop_tail(A);
		return (pal(A) && eq);
	}
}



int main () {
	srand(time(NULL));
	listn A;
	iniz_pal(A, 1);
	printL(A);
	//push_tail(A, 12);
	//push_head(A, 11);
	//printL(A);
	cout << pal(A);
	
}
