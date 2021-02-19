#include <stdio.h>
#include "bigint.h"


int main(int argc, char const *argv[]) {
    // size_t a = 576460752303423488lu;//2**59 (BASE_EXP digits)
    // size_t b = 8764607lu;
    // size_t u[] = {a,b};
    // size_t v[] = {a,b};

    // int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
    // size_t w[num_digits+1];

    // sum(num_digits, u, v, w);
    // for (int i = num_digits; i >= 0; i--) {
    //     printf("%lu", w[i]);
    // }
    // printf("\nhello %lu\n", a+a);
    // size_t *result = from_string("000000000000000456123456789012345678");
    // printf("result=%lu\n", from_string("678")[0]);
    // size_t bigint[] = {123456789012345678, 456};
    // char* result2 = to_string(result,2);
    // printf("%s", result2);

    char *result = bigsubtract("12", "13");
    printf("result=%s\n", result);
    return 0;
    //0000000000000000456123456789012345678
}