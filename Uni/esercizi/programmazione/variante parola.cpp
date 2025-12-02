#include<iostream>
#include<ctime>
using namespace std;


void print_array(char A[], const int length){
    for (int i = 0; i < length ; i=i+1)
        cout << A[i] << ' ' ;
    cout << endl ;
}

int parola (char str [], const int length, int n, char dest[]){
	bool trovato=true;
	int parole=0, lun=0, i=0, s=0;
	while (i<length && trovato){
		if (str[i]!=' ') {
			lun=lun+1;
			if (i==length-1) parole=parole+1;
		}
		if (str[i]==' ' && lun>0) {
			parole=parole+1;
		}
		if (parole==n) trovato = false;
		else if (parole>0 && str[i]==' ') lun = 0;
		i=i+1;
	}
	int c=i-lun-1;
	if (!trovato) {
		while (c<i){
		dest[s]=str[c];
		c=c+1;
		s=s+1;
		}
		return(lun);
	}
	else return (0);
}

int main (){
	const int length = 20;
	char V[] = {' ', 'r','r',' ','r',' ',' ','r',' ','r','r',' ','r','r','r',' ','r','r',' ','r'};
	char D[] = {' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	cout << parola (V, length, 5, D);
}
