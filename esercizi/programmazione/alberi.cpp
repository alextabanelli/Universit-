#include <iostream>
#include <ctime>
using namespace std ;


struct btree {
	int val;
	btree* ltree;
	btree* rtree ;
} ;
typedef btree* pbtree ;


struct stack {
	pbtree val ;
	stack* next ;
} ;
typedef stack* pstack ;




pstack push(pstack q, pbtree t){
	pstack tmp = new stack ;
	tmp->val = t ;
	tmp->next = q ;
	return(tmp) ;
}
pstack pop(pstack q) {
	if (q == NULL) return(NULL) ;
	else { pstack tmp = q ;
	q = q->next ;
	delete(tmp) ;
	return(q) ; }
}
pbtree top(pstack q) {
	if (q == NULL) return(NULL) ;
	else return(q->val);
}

void visit_it(pbtree t){
	if (t != NULL){
	ptr_btree tmp ;
	ptrt_stack p ;
	p = push(NULL, t) ;
	while (p != NULL) {
	tmp = top(p) ;
	p = pop(p) ;
	cout << tmp->val ;
	if (tmp->rtree != NULL) p = push(p, tmp->rtree) ;
	if (tmp->ltree != NULL) p = push(p, tmp->ltree) ;
		}
	}
}



pbtree create_btree(int n) {
	if (n == 0) return(NULL) ;
	else {
	pbtree t = new btree ;	
	t->val = rand()%50;
	t->ltree = create_btree(n-1) ;
	t->rtree = create_btree(n-1) ;
	return(t) ;
	}
}

void visit(pbtree t){
	if (t != NULL) { cout << t->val << ' ';
	visit(t->ltree) ;
	visit(t->rtree) ; }
}

int num_nod(pbtree t){
	if (t==NULL) return (0);
	else if (t->ltree == NULL && t->rtree == NULL) return (1);
	else return (1+num_nod(t->ltree)+num_nod(t->rtree));
}

int max_alb(pbtree t){
	int max;
	if (t == NULL) return (0);
	else if (t->ltree == NULL && t->rtree == NULL) {
		max = t->val;
		return (max);
	}
	max = t->val;
	if (max_alb(t->ltree)>max) max = max_alb(t->ltree);
	else if(max_alb(t->rtree)>max) max = max_alb(t->rtree);
	return (max);
}



int min_alb(pbtree t){
	int min;
	if (t == NULL) return (0);
	else if (t->ltree == NULL && t->rtree == NULL) {
		min = t->val;
		return (min);
	}
	min = t->val;
	if (min_alb(t->ltree)<min) min = min_alb(t->ltree);
	else if(min_alb(t->rtree)<min) min = min_alb(t->rtree);
	return (min);
}

bool is_inalb(pbtree t, int n){
	if (t == NULL) return (false);
	else if (t->val == n) return (true); 
	else return (is_inalb(t->ltree, n) || is_inalb(t->rtree, n));
}

pbtree t_inserter(pbtree t, int n){
	pbtree tmp = new pbtree;
	tmp->val = n;
	tmp->ltree = NULL;
	tmp->rtree = NULL;
	if (t == NULL) return (tmp);
	else {
		pbtree s = t;
		pbtree told = t;
		bool trovato = true;
		while (t != NULL  && trovato){
			told = t;
			if(t->val == n) trovato = false;	
			else if (t->val > n) t = t->ltree;
			else 
			t = t->rtree;
		}
		if (trovato && told->val>n) told->ltree = tmp;
		else if (trovato && told->val<n) told->rtree = tmp;
		return (s);
	}
}

int main (){
	srand(time(NULL));
	pbtree s = create_btree(4);
	visit (s);
	cout << endl;
	cout << num_nod(s);
	cout << endl << "Max: " << max_alb(s) << " Min: " << min_alb(s) << endl;
	cout << "C'e il 24: " << is_inalb(s,24);
}


