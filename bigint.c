#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"


size_t* from_string(char* str) 
{
    int num_big_digits = strlen(str) / 18 + 1;
    size_t *bigint = malloc(num_big_digits * sizeof(size_t));
    if (bigint != NULL)
    {
        char c[1];
        int decimal_digit_counter = 0;
        int big_digit_counter = 0;
        size_t big_digit = 0;
        while ((c[0] = str[decimal_digit_counter]) != '\0')
        {
            int decimal_digit = atoi(c);
            big_digit = big_digit * 10 + decimal_digit;
            if (decimal_digit_counter != 0 && decimal_digit_counter % (18-1) == 0)
            {                
                bigint[big_digit_counter++] = big_digit;
                big_digit = 0;
            }  
            decimal_digit_counter++;      
        }  
        bigint[big_digit_counter++] = big_digit;
    }
    return bigint;
}

/*
    base = 10^18 (small enough to ensure that w[i] fits in size_t)
    digits = [0, 10^18-1], u[0],v[0],w[0] contain the least significant digit
    decimal places = as many as we want to (the only limit is the physical memory of the machine)
*/
size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w) {
    size_t base = 1000000000000000000lu;//10^18
    int carry = 0;
    for (int i = 0; i < num_digits; i++) {
        w[i] = u[i] + v[i] + carry;
        carry = 0;
        if(w[i] >= base) { //overflow
            w[i] -= base;
            carry = 1;
        }
    }
    w[num_digits] = carry;
    return w;
}

// int main(int argc, char const *argv[]) {
//     size_t a = 576460752303423488lu;//2**59 (18 digits)
//     size_t b = 8764607lu;
//     size_t u[] = {a,b};
//     size_t v[] = {a,b};

//     int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
//     size_t w[num_digits+1];

//     sum(num_digits, u, v, w);
//     for (int i = num_digits; i >= 0; i--) {
//         printf("%lu", w[i]);
//     } 
//     printf("\nhello %lu\n", a+a);       
//     //printf("result=%lu", from_string("12345678901234567899")[1]);
//     return 0;
// }
