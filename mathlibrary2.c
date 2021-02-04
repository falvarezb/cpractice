#include <math.h>
#include "mathlibrary.h"

/*
    Dynamic programming implementation (bottom-up)
*/
int fib(int n) {
    int fib_terms[n];
    fib_terms[0] = 0;
    fib_terms[1] = 1;

    for(int j=2; j<=n; j++) {
        fib_terms[j] = fib_terms[j-1] + fib_terms[j-2];
    }
    return fib_terms[n];
}

int count_digits(size_t n, int base) {
    double logresult = log(n)/log(base);
    return floor(log(n)/log(base)) + 1;
}

int main(int argc, char const *argv[])
{
    int result = count_digits(1001,10);
    printf("result:%d", result);
    return 0;
}

