#include<iostream>
#include<ctime>
#include<cstring>
using namespace std;

void es2 (char A[], char B[]){
	char max[100] = "Hello";
	strcpy(max,A);
    if (strcmp(A, B)>0) strcpy(max,B);
	cout << "Il massimo vale " << max << endl;
}

int main (){
	char A[100] = "Hello C";
	char B[100] = "Hello B";
	es2 (A, B);
	return(0);
}
