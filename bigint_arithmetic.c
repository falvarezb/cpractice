#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "bigint_arithmetic.h"
#include "bigint_params.h"
#include <assert.h>
#include <stdbool.h>


/*
    classical algorithm of the sum

    base = 10^BASE_EXP
    digits = [0, 10^BASE_EXP-1], u[0],v[0],w[0] contain the least significant digit
    decimal places = as many as we want (the only limit is the physical memory of the machine)
    w = u + v
    w has an extra digit to store the final carry (either 0 or 1)
*/
uint64_t *sum(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w)
{
    int carry = 0;
    for (int i = 0; i < num_digits; i++)
    {
        w[i] = u[i] + v[i] + carry;
        carry = 0;
        if (w[i] >= BASE)
        { //overflow
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
uint64_t *subtract(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w)
{
    int borrow = 0;
    for (int i = 0; i < num_digits; i++)
    {
        uint64_t subtrahend = v[i] + borrow;
        borrow = 0;
        if (u[i] < subtrahend)
        { //overflow
            w[i] = u[i] + BASE - subtrahend;
            borrow = 1;
        }
        else
        {
            w[i] = u[i] - subtrahend;
        }
    }
    return w;
}
