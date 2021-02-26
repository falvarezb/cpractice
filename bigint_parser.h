#ifndef	BIGINT_PARSER_H
#define	BIGINT_PARSER_H

#include <stdint.h>
#include "bigint_params.h"

struct bigint from_string(char* str);
char* to_string(struct bigint bigint);
int pad_operands(struct bigint *bigint_a, struct bigint *bigint_b);
char *remove_least_significant_zeros(char *str);

#endif 