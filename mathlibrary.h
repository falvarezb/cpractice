#include <stdint.h>

/*
    Returns n-th term of Fibonacci sequence:
    fib(0) = 0
    fib(1) = 1
    fib(n) = fib(n-1) + fib(n-2)
*/
int fib(int n);

/*
    Returns an array of chars representing 2's complement m-bit representation of n 

    range of positive values: [0, 2^(m-1) - 1]
    range corresponding to negative values: [2^(m-1), 2^m - 1] that translates into the negative values [-2^(m-1), -1]
*/
char* bin(int n, int m);


int count_digits(int n);

/*
    x*y, where x,y >= 0
*/
int multiply(size_t x, size_t y);

/*
    integer division x/y, where x,y >= 0
*/
int division(size_t x, size_t y);