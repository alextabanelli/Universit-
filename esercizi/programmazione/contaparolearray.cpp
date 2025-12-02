#include<iostream>
#include<ctime>

using namespace std;

int count_wordsa(char A[], const int length){ 
        int i = 0 ;
        int res = 0;
        bool past_char_isspace = true ;
        while (i<length){
            if (past_char_isspace && (A[i] != ' '))
                res = res + 1 ;
            past_char_isspace = (A[i] == ' ');
            i = i+1 ;
        }
        return(res) ;
 }

int main (){
	char A[10] = {'a', 'd', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	cout << count_wordsa (A,10);
	return(0);
}
