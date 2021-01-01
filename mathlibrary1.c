#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "mathlibrary.h"

/*
    Recursive implementation
*/
int fib(n) {
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else{
        return fib(n-1) + fib(n-2);
    }
}


char* bin(int n, int m) {

    //if m >= size of ints, 2's complement of negative numbers does not fit into 'int'
    int sizeof_int = 8 * sizeof(int); 
    if(m >= sizeof_int && n < 0)
        return NULL;    


    //verify if n is within the range of positive/negative numbers in 2's complement m-representation
    const long unsigned_upper_bound = (long) pow(2, m);
    const int max_pos = (int) pow(2, m-1) - 1;
    const int min_neg = - (int) pow(2, m-1);

    //overflow
    if(n < min_neg || n > max_pos)
        return NULL;
    
    if(n < 0)
        n = unsigned_upper_bound + n; //2's complement    

    int digit;
    char* result = (char*) malloc((m + 1) * sizeof(char));
    if(result != NULL) {
        for(int j=m-1; j>=0; j--){
            if (n > 0) {        
                digit = n % 2;
                if(digit == 0)
                    result[j] = '0';
                else
                    result[j] = '1';
                n /= 2;        
            }
            else
                result[j] = '0';
        }

        result[m] = '\0';
    }
    return result;
}

int count_digits(int n) {
    int counter = 1;
    while((n /= 10) > 0) {
        counter++;
    }
    return counter;    
}
