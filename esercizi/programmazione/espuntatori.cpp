/*
#include <iostream>

#include <ctime>

using namespace std ;

int main (){
	int x = 0;
	int *p, *q;
	p = &x;
	q = &x;
	*p = *p+1;
	*q = *q+1;
	
	cout << p << ' ' << q << ' ' << &x << endl;
	cout << x;
	return (0); 
}

*/

/*
#include <iostream>

using namespace std ;

int main (){
	int *p = new int;
	*p = 0;
	*p = *p+1;
	cout << *p;
	delete p;
	
	return (0); 
}

*/

#include <iostream>
#include <ctime>
using namespace std ;

int main (){
	srand(time(NULL));
	int *p;
	p = new int;
	int A [10];
	int *p1;
	for (int i = 0; i<10; i = i+1){
		p = &(A[i]);
		*p = rand()%31;
		cout << *p << ' ';
	}
	
	return (0); 
}

/*
#include <iostream>
#include <ctime>
using namespace std ;

struct five {
	int uno, due, tre, quattro, cinque;
};

int main (){
	srand(time(NULL));
	int *p;
	p = new int;
	struct five b;
	p = &(b.uno);
	*p = rand()%31;
	p = &(b.due);
	*p = rand()%31;
	p = &(b.tre);
	*p = rand()%31;
	p = &(b.quattro);
	*p = rand()%31;
	p = &(b.cinque);
	*p = rand()%31;
	cout << b.uno << ' ' << b.due << ' ' << b.tre << ' ' << b.quattro << ' ' << b.cinque << ' ';
	return (0); 
}
*/

/*
#include <iostream>

using namespace std ;

int const length = 10;

void print_array(int A[], const int length){
    for (int i = 0; i < length ; i=i+1)
        cout << A[i] << ' ' ;
    cout << endl ;
}

void selc_sort(int A[], int length){
	int temp;
	int *p, *t, *q;
	t = &temp;
	for (int i = 0; i<length; i = i+1){
		for (int j = i; j<length; j = j+1){
			p = &(A[i]);
			q = &(A[j]);
			if (*q < *p){
			*t = *q;
			*q = *p;
			*p = *t;	
			}
		}
	}
}

int main (){
	int ordinare[] = {1, 4, 2, 7, 23, 56, -1, -10, 0, 90};
	print_array(ordinare, length);
	selc_sort (ordinare, length);
	print_array(ordinare, length);
	return (0); 
}
*/

