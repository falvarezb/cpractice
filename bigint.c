#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"
#include <assert.h>

const int BASE_EXP = 18; //small enough to ensure that the individual digits of bigint fit in size_t
const unsigned long BASE = 1000000000000000000; //10^BASE_EXP

/*
    Copies the digits of big_digit into the corresponding positions of 'result'
    Copy is done backwards (right to left) so that leftmost digits are the most significant ones
    If number of digits is less than BASE_POWER, the result is padded with 0s to the left
*/
void build_bigint_str(char *result, int from, size_t big_digit) {
    for (int i = BASE_EXP-1; i >= 0; i--) {
        int idx = from + i;                
        result[idx] = '0' + (big_digit % 10);
        big_digit /= 10;
    }    
}

/*
    bigint[0] is the least significat digit
    bigint[i] i=0...n-2 have exactly BASE_EXP decimal digits
    bigint[n-1] has up to BASE_EXP decimal digits

    Note: inside bigint[i] (for all i), leftmost digits are the most significant ones

    [123456789012345678,456] --> "000000000000000456123456789012345678"
*/
char* to_string(struct bigint bigint) {
    char* str = (char*) malloc((bigint.num_digits * BASE_EXP + 1) * sizeof(char));
    if (str != NULL) {        
        for (int j=0; j < bigint.num_digits; j++) {
            size_t big_digit = bigint.number[bigint.num_digits-1-j];
            build_bigint_str(str, BASE_EXP * j, big_digit);
        }
        str[bigint.num_digits * BASE_EXP] = '\0';
    }    
    return str;   
}

/*
    Converts the specified chars of 'str' into an integer 
*/
size_t build_bigint(char* str, int from, int n_digits) {
    size_t big_digit = 0;
    char c[2] = {'0', '\0'};
    int decimal_digit;
    
    for (int i = from; i < (from + n_digits); i++) {
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
struct bigint from_string(char* str) {
    int num_big_digits = strlen(str) / BASE_EXP;
    if (strlen(str) % BASE_EXP) { //digits of bigint[n-1]
        num_big_digits++;
    }
    
    size_t *bigint = (size_t*) malloc(num_big_digits * sizeof(size_t));
    if (bigint != NULL) {
        int big_digit_counter = num_big_digits - 1;

        //bigint[n-1] 
        int num_msb_decimal_digits;
        if ((num_msb_decimal_digits = strlen(str) % BASE_EXP)) {
            bigint[big_digit_counter--] = build_bigint(str, 0, num_msb_decimal_digits);
        }
    
        //bigint[0]...bigint[n-2]        
        int str_idx = num_msb_decimal_digits;        

        while (big_digit_counter >= 0) {
            bigint[big_digit_counter--] = build_bigint(str, str_idx, BASE_EXP);
            str_idx += BASE_EXP;
        }        
    }

    struct bigint result = {bigint, num_big_digits};
    return result;
}

/*
    Adds as many zeroes as needed to the right to make size of bigint equal to num_digits 
*/
size_t* pad_bigint(int original_num_digits, int new_num_digits, size_t *bigint) {
    assert (original_num_digits < new_num_digits);
    size_t* new_bigint = (size_t *) realloc(bigint, new_num_digits * sizeof(size_t));
    if (new_bigint != NULL) {
        for (int i = original_num_digits; i < new_num_digits; i++) {
            new_bigint[i] = 0;
        }        
    }
    return new_bigint;    
}

char* remove_least_significant_zeros(char* str) {
    char c;
    while ((c = *str++) == '0'){}
    return str-1;   
}

/*
    classical algorithm of the sum

    base = 10^BASE_EXP
    digits = [0, 10^BASE_EXP-1], u[0],v[0],w[0] contain the least significant digit
    decimal places = as many as we want (the only limit is the physical memory of the machine)
    w = u + v
    w has an extra digit to store the final carry (either 0 or 1)
*/
size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w) { 
    int carry = 0;
    for (int i = 0; i < num_digits; i++) {
        w[i] = u[i] + v[i] + carry;
        carry = 0;
        if(w[i] >= BASE) { //overflow
            w[i] -= BASE;
            carry = 1;
        }
    }
    w[num_digits] = carry;
    return w;
}

/*
    classical algorithm of the subtraction

    base = 10^BASE_EXP
    digits = [0, 10^BASE_EXP-1], u[0],v[0],w[0] contain the least significant digit
    decimal places = as many as we want (the only limit is the physical memory of the machine)
    w = u - v, where u >= v
*/
size_t* subtract(int num_digits, size_t *u, size_t *v, size_t *w) {     
    int borrow = 0;
    for (int i = 0; i < num_digits; i++) {
        size_t subtrahend = v[i] + borrow;
        borrow = 0;
        if (u[i] < subtrahend) { //overflow
            w[i] = u[i] + BASE - subtrahend;
            borrow = 1;
        }
        else {
            w[i] = u[i] - subtrahend;
        }
    }
    return w;
}

/*
    Adds as many zeroes as needed to the right so that both operands have the same length
*/
int pad_operands(struct bigint bigint_a, struct bigint bigint_b) {
    struct bigint least_bigint, greatest_bigint;

    if (bigint_a.num_digits == bigint_b.num_digits) {
        return EXIT_SUCCESS;
    }

    if (bigint_a.num_digits < bigint_b.num_digits) {
        least_bigint = bigint_a;
        greatest_bigint= bigint_b;   
    }
    else if (bigint_a.num_digits > bigint_b.num_digits) {
        least_bigint = bigint_b;
        greatest_bigint = bigint_a;  
    }

    size_t* padded_bigint = pad_bigint(least_bigint.num_digits, greatest_bigint.num_digits, least_bigint.number);
    if (padded_bigint != NULL) {
        least_bigint.number = padded_bigint;
        least_bigint.num_digits = greatest_bigint.num_digits;
        return EXIT_SUCCESS; 
        
    }
    return EXIT_FAILURE;
}

int largest_operand(struct bigint bigint_a, struct bigint bigint_b) {
    if (bigint_a.num_digits > bigint_b.num_digits) {
        return 1;
    }
    else if (bigint_a.num_digits < bigint_b.num_digits) {
        return 2;
    }

    int j = bigint_a.num_digits - 1;
    while (j >= 0 && bigint_a.number[j] == bigint_b.number[j]) {
        j--;
    } 

    if (j == -1) {
        return 0;
    }    
    else if (bigint_a.number[j] > bigint_b.number[j]) {
        return 1;
    }

    return 2;
}

char* bigsum(char* a, char* b) {
    struct bigint bigint_a = from_string(a);
    if (bigint_a.number == NULL) return NULL;
    struct bigint bigint_b = from_string(b);
    if (bigint_b.number == NULL) return NULL;

    if(pad_operands(bigint_a, bigint_b) == EXIT_FAILURE) return NULL;
    
    assert (bigint_a.num_digits == bigint_b.num_digits);
    size_t result_size = bigint_a.num_digits + 1; //extra digit for the final carry
    size_t result[result_size];
    
    sum(bigint_a.num_digits, bigint_a.number, bigint_b.number, result);
    return remove_least_significant_zeros(to_string((struct bigint) {result, result_size}));
}

char* bigsubtract(char* a, char* b) {
    struct bigint bigint_a = from_string(a);
    struct bigint bigint_b = from_string(b);

    int lgest_operand = largest_operand(bigint_a, bigint_b);

    if(pad_operands(bigint_a, bigint_b) == EXIT_FAILURE) {
        return NULL;
    }

    size_t result_size = bigint_a.num_digits;
    size_t result[result_size];
      

    if (lgest_operand == 0) {
        return "0";
    }    
    else if (lgest_operand == 1) {
        subtract(bigint_a.num_digits, bigint_a.number, bigint_b.number, result);
        return remove_least_significant_zeros(to_string((struct bigint) {result, result_size}));
    }
    else {        
        subtract(bigint_a.num_digits, bigint_b.number, bigint_a.number, result);  
        char* subtract_str = to_string((struct bigint) {result, result_size});  
        char* result_str = remove_least_significant_zeros(subtract_str);
        char* signed_result = (char*) malloc((strlen(result_str)+ 2) * sizeof(char));
        signed_result[0] = '-';
        signed_result[1] = '\0';        
        strcat(signed_result, result_str); 
        free(subtract_str); 
        return signed_result;   
    }
    

    
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
//     // size_t *result = from_string("000000000000000456123456789012345678");    
//     // printf("result=%lu\n", from_string("678")[0]);
//     // size_t bigint[] = {123456789012345678, 456};
//     // char* result2 = to_string(result,2);
//     // printf("%s", result2);

//     char *result = bigsum("12", "12");
//     printf("result=%s\n", result);
//     return 0;
//     //0000000000000000456123456789012345678
// }
