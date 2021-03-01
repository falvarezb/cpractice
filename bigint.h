#ifndef	BIGINT__H
#define	BIGINT__H

#include <stdint.h>

#define BASE_EXP  18                   //small enough to ensure that the individual digits of bigint fit in uint64_t
#define BASE 1000000000000000000 //10^BASE_EXP

struct bigint {
    uint64_t *number;
    int num_digits;
};
char* bigsum(char* a, char* b);
char* bigsubtract(char* a, char* b);
uint64_t* sum(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w);
uint64_t* subtract(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w);
struct bigint from_string(char* str);
char* to_string(struct bigint bigint);
int pad_operands(struct bigint *bigint_a, struct bigint *bigint_b);
char *remove_least_significant_zeros(char *str);

#endif /* BIGINT__H */