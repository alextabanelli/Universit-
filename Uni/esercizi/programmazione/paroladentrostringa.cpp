#include<iostream>
#include<ctime>
#include<cstring>
using namespace std;

int count_words(char A[]){ // Precondition: A contains '\0'
		//cerco gh e ch nella stringa
        int res = 0 ;
        int i = 0 ;
        bool past_char_isspace = true ;
        while (A[i] != '\0' ){
            if (past_char_isspace && (A[i] == 'h'))
                res = res + 1 ;
            past_char_isspace = (A[i] == 'g' || A[i] == 'c');
            i = i+1 ;
        }
        return(res) ;
 }

int main (){
	char A[100] = "Hello ww ch ciao w";
	cout << count_words (A);
	return(0);
}
