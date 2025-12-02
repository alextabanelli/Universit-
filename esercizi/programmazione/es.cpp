#include <iostream>
using namespace std;

int m ;
 int n ;
 void min(){
int tmp ;
if (m > n) { tmp = m ; m = n ; n = tmp ; }
 }
 int main() {
cin >> m >> n ; // m = 10 ; n = 5
{ int m = 7 ;
min() ;
cout << m << n ;
}
return(0) ;
 }
