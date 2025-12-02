#include<iostream>
#include<ctime>
#include<cstring>
using namespace std;

void max3string (char A[], char B[], char C[]){
	char max[100] = "Hello";
	strcpy(max,A);
    if (strlen(C)>strlen(A)) strcpy(max,C);
	else if (strlen(B)>strlen(A)) strcpy(max,B);
	if (strlen(B)>strlen(C) && strlen(C)>strlen(A)) strcpy(max,B);
	cout << "Il massimo vale " << max << endl;
}

int main (){
	char A[100] = "Hello www";
	char B[100] = "Hello  ikujyhtgvfd";
	char C[100] = "Hello ";
	max3string (A, B, C);
	return(0);
}
