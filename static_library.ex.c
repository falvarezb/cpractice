#include <stdio.h>
#include "strlibrary.h"
#include "mathlibrary.h"

int main(int argc, char const *argv[])
{
    const char *greeting = "hell o";
    printf("%s\n", strip_blanks(greeting));
    int n = 10;
    int base = 2;
    printf("number of digits of %d in base %d is %d\n", n, base, count_digits(n, base));
    return 0;
}
