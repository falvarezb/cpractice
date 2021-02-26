#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint_parser.h"
#include "bigint_params.h"
#include <assert.h>
#include <stdbool.h>


/*
    Copies the digits of big_digit into the corresponding positions of 'result'
    Copy is done backwards (right to left) so that leftmost digits are the most significant ones
    If number of digits is less than BASE_POWER, the result is padded with 0s to the left
*/
void build_bigint_str(char *result, int from, uint64_t big_digit)
{
    for (int i = BASE_EXP - 1; i >= 0; i--)
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

    Note: inside bigint[i] (for all i), leftmost digits are the most significant ones

    [123456789012345678,456] --> "000000000000000456123456789012345678"
*/
char *to_string(struct bigint bigint)
{
    char *str = (char *)malloc((bigint.num_digits * BASE_EXP + 1) * sizeof(char));
    if (str != NULL)
    {
        for (int j = 0; j < bigint.num_digits; j++)
        {
            uint64_t big_digit = bigint.number[bigint.num_digits - 1 - j];
            build_bigint_str(str, BASE_EXP * j, big_digit);
        }
        str[bigint.num_digits * BASE_EXP] = '\0';
    }
    return str;
}

/*
    Converts the specified chars of 'str' into an integer 
*/
uint64_t build_bigint(char *str, int from, int n_digits)
{
    uint64_t big_digit = 0;
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
struct bigint from_string(char *str)
{
    int num_big_digits = strlen(str) / BASE_EXP;
    if (strlen(str) % BASE_EXP)
    { //digits of bigint[n-1]
        num_big_digits++;
    }

    uint64_t *bigint = (uint64_t *)malloc(num_big_digits * sizeof(uint64_t));
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

    struct bigint result = {bigint, num_big_digits};
    return result;
}

/*
    Adds as many zeroes as needed to the right to make size of bigint equal to num_digits 
*/
uint64_t *pad_bigint(int original_num_digits, int new_num_digits, uint64_t *bigint)
{
    assert(original_num_digits < new_num_digits);
    uint64_t *new_bigint = (uint64_t *)realloc(bigint, new_num_digits * sizeof(uint64_t));
    if (new_bigint != NULL)
    {
        for (int i = original_num_digits; i < new_num_digits; i++)
        {
            new_bigint[i] = 0;
        }
    }
    return new_bigint;
}

char *remove_least_significant_zeros(char *str)
{
    char c;
    while ((c = *str++) == '0')
        ;

    if (*(str - 1) == '\0') //result is 0
        return str - 2;

    return str - 1;
}


/*
    Adds as many zeroes as needed to the right so that both operands have the same length
*/
int pad_operands(struct bigint *bigint_a, struct bigint *bigint_b)
{
    struct bigint *least_bigint, *greatest_bigint;

    if (bigint_a->num_digits == bigint_b->num_digits)
    {
        return EXIT_SUCCESS;
    }
    else if (bigint_a->num_digits < bigint_b->num_digits)
    {
        least_bigint = bigint_a;
        greatest_bigint = bigint_b;
    }
    else
    {
        least_bigint = bigint_b;
        greatest_bigint = bigint_a;
    }

    uint64_t *padded_bigint = pad_bigint(least_bigint->num_digits, greatest_bigint->num_digits, least_bigint->number);
    if (padded_bigint != NULL)
    {
        least_bigint->number = padded_bigint;
        least_bigint->num_digits = greatest_bigint->num_digits;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}



