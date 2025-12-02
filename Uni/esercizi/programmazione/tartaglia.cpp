#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int x, y, z, n, w, k, f, g;
    long double fattorialen = 1, fattorialeg = 1, fattorialek = 1, divisore;
    cout << "Dammi n " << endl;
    cin >> x;
    //z = 1; //quanto scrivere nella riga
    //ciclo per quante righe scrivere
    for (z = 1; z<x+1; z=z+1){
        if (z == 1) cout << " " << "1" << " " << endl;
        //ciclo per quante volte scrivere in una riga
        n = z;
        while(n>1){
            fattorialen = fattorialen*n;
            n = n-1;
        }
       for (int i = 0; i < z+1; i=i+1) {
           //
           k = i;
           g = n-k;
               //ciclo fattoriale k
               while(g>1){
                     fattorialeg = fattorialeg*g;
                     g = g-1;
               }
               while(k>1){
                     fattorialek = fattorialek*g;
                     k = k-1;
               }
           if (g == 0 || g == 1) fattorialeg=1;
           if (g == 0 || g == 1) fattorialeg=1;
           cout << " " << fattorialen/(fattorialeg*fattorialek) << " ";

       } cout << endl;
    } if (z == 0) cout << "1" << endl;
    return 0;
}
