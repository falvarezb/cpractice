#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

void build_bigint_str(char *result, int from, size_t big_digit)
{
    while (big_digit > 0)
    {                
        result[from++] = '0' + (big_digit % 10);
        big_digit /= 10;
    }
    result[from] = '\0';
}

void build_bigint_str2(char *result, int from, size_t big_digit)
{
    int local_digit_counter = 18;    
    while (big_digit > 0)
    {
        int idx = from + local_digit_counter;                
        result[idx] = '0' + (big_digit % 10);
        big_digit /= 10;
        local_digit_counter--;
    }
}

/*
    bigint[0] is the least significat digit
    bigint[i] i=0...n-2 have exactly 18 decimal digits
    bigint[n-1] has up to 18 decimal digits

    [123456789012345678,456] --> "456123456789012345678"
*/
char* to_string(size_t *bigint, int num_big_digits)
{
    char* str = (char*) malloc((num_big_digits * 18 + 1) * sizeof(char));
    if (str != NULL)
    {
        

        //bigint[n-1]         
        char local_str[18+1];
        size_t big_digit = bigint[num_big_digits-1];
        build_bigint_str(local_str, 0, big_digit);
        //reverse digits order
        for (int i = strlen(local_str)-1; i >= 0; i--)
        {
            str[strlen(local_str)-1 - i] = local_str[i];
        }

        int first_element_offset = strlen(local_str) - 1;
        
        //bigint[0]...bigint[n-2]
        for (int j=1; j <= num_big_digits-1; j++)
        {
            big_digit = bigint[num_big_digits-1-j];
            build_bigint_str2(str, first_element_offset + 18 * (j-1), big_digit);
        }
        str[num_big_digits * 18 + 1] = '\0';
    }    
    return str;   
}


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
    bigint[i] i=0...n-2 have exactly 18 decimal digits
    bigint[n-1] has up to 18 decimal digits

    "456123456789012345678" --> [123456789012345678,456]
*/
size_t* from_string(char* str) 
{
    int num_big_digits = strlen(str) / 18;
    if (strlen(str) % 18)//digits of bigint[n-1]
    {
        num_big_digits++;
    }
    
    size_t *bigint = (size_t*) malloc(num_big_digits * sizeof(size_t));
    if (bigint != NULL)
    {
        int big_digit_counter = num_big_digits - 1;

        //bigint[n-1] 
        int num_msb_decimal_digits;
        if ((num_msb_decimal_digits = strlen(str) % 18))
        {
            bigint[big_digit_counter--] = build_bigint(str, 0, num_msb_decimal_digits);
        }
    
        //bigint[0]...bigint[n-2]        
        int str_idx = num_msb_decimal_digits;        

        while (big_digit_counter >= 0)
        {
            bigint[big_digit_counter--] = build_bigint(str, str_idx, 18);
            str_idx += 18;
        }        
    }
    return bigint;
}

/*
    classical algorithm of the sum

    base = 10^18 (small enough to ensure that w[i] fits in size_t)
    digits = [0, 10^18-1], u[0],v[0],w[0] contain the least significant digit
    decimal places = as many as we want (the only limit is the physical memory of the machine)
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
//     // size_t a = 576460752303423488lu;//2**59 (18 digits)
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
//     printf("result=%lu\n", from_string("123456789012345678")[0]);
//     //size_t bigint[] = {123456789012345678, 456};
//     //printf("%s", to_string(bigint,2));
//     return 0;
// }
