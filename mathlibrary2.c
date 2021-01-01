#include "mathlibrary.h"

/*
    Dynamic programming implementation (bottom-up)
*/
int fib(n) {
    int fib_terms[n];
    fib_terms[0] = 0;
    fib_terms[1] = 1;

    for(int j=2; j<=n; j++) {
        fib_terms[j] = fib_terms[j-1] + fib_terms[j-2];
    }
    return fib_terms[n];
}
