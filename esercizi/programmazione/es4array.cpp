#include<iostream>
#include<ctime>
using namespace std;

void print_array(char A[], const int length){
    for (int i = 0; i < length ; i=i+1)
        cout << A[i] << ' ' ;
    cout << endl ;
}

int firstword (char V [], const int length, int i){
	
	bool trovato=true;
	int lun = 0;
	while (trovato && i<length){
		if (V[i]!=' ') lun = lun+1;
		if (V[i]==' ' && lun>0) trovato = false;
		i = i+1;
	}
	return (lun);
}

void copydest (char V [], const int length, int i, char dest[]){
	
	bool trovato=true;
	int lun = 0;
	while (trovato && i<length){
		if (V[i]!=' ') {
			lun = lun+1;
			dest[i]=V[i];
		}
		if (V[i]==' ' && lun>0) trovato = false;
		i = i+1;
	}
}

int wordbi (char V [], const int length,int i){
	
	bool trovato=true;
	bool endword=false;
	int lun = 0, bi = 0;
	while (trovato && i<length){
		if (V[i]!=' ') lun = lun+1;
		else bi=bi+1;
		if (V[i]==' ' && lun>0) endword = true;
		if (V[i]!=' ' && endword) trovato = false;
		i = i+1;
	}lun=lun-1;
	return (lun+bi);
}



int parola (char str [], const int length, int n, char dest[]){
	
	bool trovato=true;
	int parole = 0, i =0;
	int differenza = 0;
	while (trovato && i<length){
		//cout << "Lunghezza Prima parola: " << firstword(str, length,i) << endl;
		if (firstword(str, length,i)>0) {
			parole=parole+1	;
			differenza = differenza+wordbi(str, length,i);
			//cout << "Parola con bianchi: " << wordbi(str, length,i) << endl;
			if (parole==n) trovato = false;
			else if (i ==19) {
				trovato = false;
				parole=0;
			}
			else i = differenza;
			cout << "I: " << i << endl;
			
		}
	}if (parole==0) return (0);
	else {
	copydest (str, length, i, dest);
	return(firstword(dest, length,i));
	}
}

int main (){
	const int length = 20;
	char V[] = {' ', 'r','r',' ','r',' ',' ','r','r','r','r',' ','r','r','r',' ','r','r',' ','r'};
	char D[] = {' ', ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
	cout << parola (V, length, 1, D) << endl;
	print_array(D, length);
	//print_array(V, length);
}
