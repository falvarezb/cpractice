#ifndef	BIGINT_H
#define	BIGINT_H

#include <stddef.h>

size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w);
size_t* subtract(int num_digits, size_t *u, size_t *v, size_t *w);
struct bigint from_string(char* str);
char* to_string(struct bigint bigint);
char* bigsum(char* a, char* b);
char* bigsubtract(char* a, char* b);

struct bigint {
    size_t *number;
    int num_digits;
};

#endif 