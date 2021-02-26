#ifndef	BIGINT_PARAMS_H
#define	BIGINT_PARAMS_H

#include <stdint.h>

#define BASE_EXP  18                   //small enough to ensure that the individual digits of bigint fit in uint64_t
#define BASE 1000000000000000000 //10^BASE_EXP

struct bigint {
    uint64_t *number;
    int num_digits;
};

#endif 