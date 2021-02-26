#ifndef	BIGINT_ARITHMETIC_H
#define	BIGINT_ARITHMETIC_H

#include <stdint.h>

uint64_t* sum(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w);
uint64_t* subtract(int num_digits, uint64_t *u, uint64_t *v, uint64_t *w);

#endif 