#include <iostream>
#include <ctime>
using namespace std ;

//es 1
/*
struct Node {
	int elem;
	Node* next;
};


struct Stack {
	Node* top;
};

void init(Stack& s) {
	s.top = NULL;
}

void push(Stack& s, int elem) {
	Node* p = new Node;
	p->elem = elem;
	p->next = s.top;
	s.top = p;
}

void pop(Stack& s, int elem) {
	Node* p = s.top->next;
	delete s.top;
	s.top = p;
}

int top(const Stack& s) {
	if (s.top == NULL) return (-1);
	else return (s.top->elem);
}
*/

//es 2

struct Node {
	int elem;
	Node* next;
};


struct Queue {
	Node* head; 
	Node* tail; 
};

void printQ(const  Queue s){
	Node* p = s.head;
	while (p != NULL){
		cout << p->elem << ' ';
		p = p->next;
	}
	cout << endl;
}

void init(Queue& q) {
	q.head = NULL;
	q.tail = NULL;
}


bool empty(Queue& q) {
	if (q.head == NULL) return (true);
	else return (false);
}

void enqueue(Queue& q, int elem) {
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

void dequeue(Queue& q) {
	q.head = q.head->next;
}

int head(const Queue& q) {
	if (q.head != NULL) return (q.head->elem);
	else return (-1);
}


int tail(const Queue& q) {
	if (q.tail != NULL) return (q.tail->elem);
	else return (-1);
}


//es 3
/*
struct Node {
	int elem;
	Node* next;
};


struct Set {
	Node* data; 
};

void init(Set& s) {
	s.data = NULL;
}

bool empty(const Set& s) {
	if (s.data == NULL) return true;
	else return false;
}

void insert(Set& s, int elem) {
	Node* p = s.data;
	Node* prev  = NULL;
	while (p != NULL && p->elem < elem){
			prev = p;
			p = p->next;
	}
	if (p == NULL || p->elem != elem){
		Node* q = new Node;
		q->elem = elem;	
		q->next = p;
		if (prev == NULL) s.data = q;
		else prev->next = q;		
	} //else cout << "Elemento gia' presente" << endl;
	
}

void printS(const Set s){
	Node* p = s.data;
	while (p != NULL){
		cout << p->elem << ' ';
		p = p->next;
	}
	cout << endl;
}

void remove(Set& s, int elem) {
	Node* p = s.data;
	Node* prev  = NULL;
	while (p != NULL && p->elem != elem){
			prev = p;
			p = p->next;
	}
	if (p != NULL && p->elem == elem){
		if (prev == NULL){
			s.data = s.data->next;
		}
		else {
			Node* q = p->next;
			delete p;
			prev->next = q;
		}		
	} else cout << "Elemento non presente" << endl;
}

bool member(const Set& s, int elem) {
	bool trovato = true;
	Node* p = s.data;
	while (p != NULL && trovato){
		if (p->elem == elem) trovato = false;
		else p = p->next;
	}
	return (!trovato);
}

Set set_union(const Set& s, const Set& t) {
	Set uni;
	init (uni);
	Node* p = s.data;
	Node* q = t.data;
	while (p != NULL){
		insert(uni, p->elem);
		p = p->next;	
	}
	while (q != NULL){
		if (!(member(uni,q->elem))){
			insert(uni, q->elem);
		} else q = q->next;	
	}
	return (uni);
}

Set set_intersection(const Set& s, const Set& t) {
	Set uni;
	init(uni);
	Node* p = s.data;
	Node* q = t.data;
	while (p != NULL){
		while (q != NULL){
			if ( member(s,p->elem) && member(t,p->elem) ){
				insert(uni, p->elem);
			}
			q = q->next;	
		}
		p = p->next;
		q = t.data;
	}
	return (uni);
}


Set set_difference(const Set& s, const Set& t) {
	Set uni;
	init(uni);
	Node* p = s.data;
	Node* q = t.data;
	while (p != NULL){
		while (q != NULL){
			if ( !member(t,p->elem) ){
				insert(uni, p->elem);
			}
			q = q->next;	
		}
		p = p->next;
		q = t.data;
	}
	return (uni);
}
*/

int main (){
	srand(time(NULL));
	Queue in1;
	init(in1);
	printQ(in1);
	enqueue(in1, 15);
	printQ(in1);
	for (int i = 0; i<20; i = i+1){
		enqueue(in1, rand()%20);
	}
	printQ(in1);
	dequeue(in1);
	printQ(in1);
	cout << "Testa: " << head(in1) << " Coda: " << tail(in1) << endl;
}
