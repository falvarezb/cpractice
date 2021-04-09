#include <stdio.h>
//int var1=1, var2=2, var3=8, var4=16, var5=32;
//int myarray[];
int var1 = 1;
int var2 = 2;

int main(int argc, char const *argv[])
{
    // for (size_t i = 0; i < 1000; i++)
    // {
    //     myarray[i] = 1;
    // }
    // printf("%d\n", myarray[0]);
    // myarray[1] = 2;
    // printf("%d\n", myarray[1]);
    printf("var1=%d\n", var1);
    printf("var2=%d\n", var2);
    int *ptr = &var1;
    *(ptr+=1) = 3;
    printf("ptr=%p\n", ptr);
    printf("var2=%d\n", var2);

    return 0;
}
