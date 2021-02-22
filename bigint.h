#ifndef	BIGINT_H
#define	BIGINT_H

#include <stddef.h>

uint64_t* sum(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w);
uint64_t* subtract(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w);
struct bigint from_string(char* str);
char* to_string(struct bigint bigint);
char* bigsum(char* a, char* b);
char* bigsubtract(char* a, char* b);

struct bigint {
    uint64_t *number;
    int num_digits;
};

#endif 