#include <stddef.h>

#define BASE_EXP 18 //small enough to ensure that the individual digits of bigint fit in size_t

size_t* sum(int num_digits, size_t *u, size_t *v, size_t *w);
size_t* from_string(char* str);
char* to_string(size_t *number, int num_big_digits);