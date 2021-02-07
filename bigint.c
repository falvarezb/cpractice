#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

/*
    Copies the digits of big_digit into the corresponding positions of 'result'
    Copy is done backwards (right to left) so that leftmost digits are the most significant ones
    If number of digits is less than BASE_POWER, the result is padded with 0s to the left
*/
void build_bigint_str(char *result, int from, size_t big_digit)
{
    for (int i = BASE_EXP-1; i >= 0; i--)
    {
        int idx = from + i;                
        result[idx] = '0' + (big_digit % 10);
        big_digit /= 10;
    }    
}

/*
    bigint[0] is the least significat digit
    bigint[i] i=0...n-2 have exactly BASE_EXP decimal digits
    bigint[n-1] has up to BASE_EXP decimal digits

    Note: inside bigint[i] (for all i), lestmost digits are the most significant ones

    [123456789012345678,456] --> "000000000000000456123456789012345678"
*/
char* to_string(size_t *bigint, int num_big_digits)
{
    char* str = (char*) malloc((num_big_digits * BASE_EXP + 1) * sizeof(char));
    if (str != NULL)
    {        
        for (int j=0; j < num_big_digits; j++)
        {
            size_t big_digit = bigint[num_big_digits-1-j];
            build_bigint_str(str, BASE_EXP * j, big_digit);
        }
        str[num_big_digits * BASE_EXP] = '\0';
    }    
    return str;   
}

/*
    Converts the specified chars of 'str' into an integer 
*/
size_t build_bigint(char* str, int from, int n_digits)
{
    size_t big_digit = 0;
    char c[2] = {'0', '\0'};
    int decimal_digit;
    
    for (int i = from; i < (from + n_digits); i++)
    {
        c[0] = str[i];        
        decimal_digit = atoi(c);
        big_digit = big_digit * 10 + decimal_digit;
    }
    return big_digit; 
}

/*
    bigint[0] is the least significat digit
    bigint[i] i=0...n-2 have exactly BASE_EXP decimal digits
    bigint[n-1] has up to BASE_EXP decimal digits

    "456123456789012345678" --> [123456789012345678,456]
*/
size_t* from_string(char* str) 
{
    int num_big_digits = strlen(str) / BASE_EXP;
    if (strlen(str) % BASE_EXP)//digits of bigint[n-1]
    {
        num_big_digits++;
    }
    
    size_t *bigint = (size_t*) malloc(num_big_digits * sizeof(size_t));
    if (bigint != NULL)
    {
        int big_digit_counter = num_big_digits - 1;

        //bigint[n-1] 
        int num_msb_decimal_digits;
        if ((num_msb_decimal_digits = strlen(str) % BASE_EXP))
        {
            bigint[big_digit_counter--] = build_bigint(str, 0, num_msb_decimal_digits);
        }
    
        //bigint[0]...bigint[n-2]        
        int str_idx = num_msb_decimal_digits;        

        while (big_digit_counter >= 0)
        {
            bigint[big_digit_counter--] = build_bigint(str, str_idx, BASE_EXP);
            str_idx += BASE_EXP;
        }        
    }
    return bigint;
}

/*
    classical algorithm of the sum

    base = 10^BASE_EXP
    digits = [0, 10^BASE_EXP-1], u[0],v[0],w[0] contain the least significant digit
    decimal places = as many as we want (the only limit is the physical memory of the machine)
*/
size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w) {
    size_t base = 1000000000000000000lu;//10^BASE_EXP
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
//     // size_t a = 576460752303423488lu;//2**59 (BASE_EXP digits)
//     // size_t b = 8764607lu;
//     // size_t u[] = {a,b};
//     // size_t v[] = {a,b};

//     // int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
//     // size_t w[num_digits+1];

//     // sum(num_digits, u, v, w);
//     // for (int i = num_digits; i >= 0; i--) {
//     //     printf("%lu", w[i]);
//     // } 
//     // printf("\nhello %lu\n", a+a);   
//     size_t *result = from_string("000000000000000456123456789012345678");    
//     printf("result=%lu\n", from_string("678")[0]);
//     // size_t bigint[] = {123456789012345678, 456};
//     // char* result2 = to_string(result,2);
//     // printf("%s", result2);
//     return 0;
//     //0000000000000000456123456789012345678
// }
