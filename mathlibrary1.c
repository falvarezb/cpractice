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
    int byte_length_in_bits = 8;
    int sizeof_int_in_bits = byte_length_in_bits * sizeof(int); 
    if(m >= sizeof_int_in_bits && n < 0)
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

/*
    O(log) implementation
 */ 
int multiply(size_t x, size_t y) {
    size_t sum = 0;
    size_t shiftedX = x;
    int byte_length_in_bits = 8;
    int sizeof_int_in_bits = byte_length_in_bits * sizeof(int); 

    for(int j=0; j<sizeof_int_in_bits; j++){
        if(y & (1 << j)) {
            sum += shiftedX;
        }
        shiftedX <<= 1;
    }
    return sum;
}

/*
    O(log) implementation
 */ 
int divide(size_t x, size_t y) {
    size_t q = 0; //quotient    
    int byte_length_in_bits = 8;
    int sizeof_int_in_bits = byte_length_in_bits * sizeof(int);
    size_t shiftedY = y << sizeof_int_in_bits;

    for(int j=sizeof_int_in_bits-1; j>=0; j--){
        q <<= 1;    
        shiftedY >>= 1; 
        if(x >= shiftedY) {
            x -= shiftedY;            
            q++;
        }        
    }
    return q;
}

// int main(int argc, char const *argv[])
// {
//     int result = divide(65,5);
//     printf("result=%d", result);
//     return 0;
// }
