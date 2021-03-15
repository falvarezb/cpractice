#include <stdio.h>
#include<string.h>


typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) { 
    int i;
    for (i=0;i<len;i++) 
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_int(int x) { 
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_long(long x) { 
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_float(float x) { 
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) { 
    show_bytes((byte_pointer) &x, sizeof(void *));
}

int main() {

    printf("%ld\n", __STDC_VERSION__);

    show_int(0x0000000000000042);
    show_long(0x0000000000000042);
    // show_pointer(&i);
    //show_float(1);

    // int a = 0x12345678;
    // byte_pointer ap = (byte_pointer) &a; 
    // show_bytes(ap, 1); /* A. */ 
    // show_bytes(ap, 2); /* B. */ 
    // show_bytes(ap, 3); /* C. */ 

    // show_bytes((byte_pointer) &"12345", sizeof("12345"));
}

