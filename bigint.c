#include <stdio.h>

size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w);

/*
    Algorithm:
    carry = 0

    while i < num_digits
        w[i] = u[i] + v[i] + carry
        if w[i] > base
            w[i] = w[i] mod base
            carry = 1

    if we make base = number of bits used to represent u,v,w
    then mod is automatically applied.

    thus we need a way to detect when overflow happens. 
    for that we can rely on the fact that, when there is overflow:
    a + b < a
    a + b < b
*/
size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w) {
    int carry = 0;
    for (int i = 0; i < num_digits; i++) {
        w[i] = u[i] + carry;
        if(w[i] < carry) { //overflow
            carry = 1;
        }

        w[i] += v[i];
        if(w[i] < v[i]) { //overflow
            carry = 1;
        }
    }
    w[num_digits] = carry;
    return w;
}

int main(int argc, char const *argv[]) {
    int num_digits = 1;
    size_t a = 9223372036854775808ul;
    size_t u[] = {a};
    size_t v[] = {a};
    size_t w[num_digits+1];
    sum(num_digits, u, v, w);
    for (int i = num_digits; i >= 0; i--) {
        printf("%d", w[i]);
    } 
    printf("\n%ul\n", a+a);       
    return 0;
}
