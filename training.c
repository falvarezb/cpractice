#include <stdio.h>

size_t count_chars();
unsigned getbits(unsigned x, int p, int n);
int bitcount(unsigned x);
int bitcount0(unsigned x);

int main(int argc, char const *argv[])
{
    /* code */ 
    printf("chars:%zu\n", count_chars());
    printf("last bits:%u\n", getbits(37, 3, 3));
    printf("bitcount:%d\n", bitcount(37));
    printf("bitcount0:%d\n", bitcount0(5));
    return 0;
}


size_t count_chars() {
    int c;
    size_t counter = 0;

    while ((c = getchar()) != EOF)
        counter++;
    
    return counter  ;  
}

 /* 
 getbits:  get n bits from position p counting from the left and starting at 0 
 */
unsigned getbits(unsigned x, int p, int n)
{
    //mask to select last n digits
    int mask = ~(-1 << n);
    return (x >> (p+1-n)) & mask;
}

/* bitcount:  count 1 bits in x */
int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if (x & 1)
            b++;
    return b;
}

/* bitcount:  count 0 bits in x */
int bitcount0(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1)
        if ((x & 1) == 0)
            b++;
    return b;
}

