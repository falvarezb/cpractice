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

int count_digits(size_t n, int base) {    
    int counter = 1;
    while((n /= base) > 0) {
        counter++;
    }
    return counter;    
}

/*
    O(log) implementation
    classic multiplication algorithm in binary
 */ 
int multiply(int x, int y) {
    int sum = 0;
    int shiftedX = x;
    int number_digits = count_digits(y, 2);

    int bit_selector = 1;
    int digit_counter = 0;
    while(digit_counter < number_digits){
        if(y & bit_selector) {
            sum += shiftedX;
        }
        bit_selector <<= 1;
        shiftedX <<= 1;
        digit_counter++;
    }
    return sum;
}

/*
    O(log) implementation
    classic division algorithm in binary
 */ 
int divide(size_t x, size_t y) {
    size_t q = 0; //quotient    
    int number_digits = count_digits(x, 2) - count_digits(y, 2);
    size_t shiftedY = y << number_digits;

    int digit_counter = 0;
    while(digit_counter < number_digits){
        q <<= 1;    
        shiftedY >>= 1; 
        if(x >= shiftedY) {
            x -= shiftedY;            
            q++;
        }
        digit_counter++;    
    }
    return q;
}

// int main(int argc, char const *argv[])
// {
//     int result = multiply(2,-3);
//     printf("result=%d", result);
//     return 0;
// }
