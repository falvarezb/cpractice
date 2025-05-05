/**
 * See https://github.com/falvarezb/cpractice?tab=readme-ov-file#object-representation
 **/


#include <stdio.h>
#include <stdalign.h>
#include <arpa/inet.h>

#define OBJ_REPR(obj) obj_repr(&(obj), sizeof(obj))

void obj_repr(void* obj, size_t len) {
    unsigned char* ptr = (unsigned char*)obj;
    for (size_t i = 0; i < len; i++)
        printf("%.2x ", ptr[i]);
    printf("\n");
}

int main() {

    int obj1 = 0x2842;
    long obj2 = 0x2842;


    //MULTI-BYTE INTEGERS

    //Little-endian representation (least significant bytes are stored at the lowest addresses)
    //(little-endian is the default option in x86 platforms)
    printf("Little-endian representation\n");

    printf("obj1 = ");
    OBJ_REPR(obj1); //42 28 00 00 -> 4 bytes
    printf("obj2 = ");
    OBJ_REPR(obj2); //42 28 00 00 00 00 00 00 -> 8 bytes

    //Big-endian representation (used in network protocols)
    printf("Big-endian representation\n");
    int obj1_bigend = htonl(obj1);
    long obj2_bigend = htonll(obj2);
    printf("obj1 = ");
    OBJ_REPR(obj1_bigend); //00 00 28 42 -> 4 bytes
    printf("obj2 = ");
    OBJ_REPR(obj2_bigend); //00 00 00 00 00 00 28 42 -> 8 bytes

    // Format specifiers for printing integers always use big-endian representation
    printf("Format specifiers for printing integers always use big-endian representation\n");
    printf("obj1 = %x\n", obj1); // 28 42 (leading zeros are omitted as not padding has been specified)
    printf("obj2 = %lx\n", obj2); // 28 42 (leading zeros are omitted as not padding has been specified)

    //CHARACTER STRINGS    
    printf("character strings representation\n");
    printf("12345 = ");
    OBJ_REPR("12345"); //31 32 33 34 35 00 -> 6 bytes, including final null byte '\0'


    //ALIGNMENT

    printf("alignof(int) %zu\n", alignof(int));

    struct X {
        int n;  // size: 4, alignment: 4
        char c; // size: 1, alignment: 1
        // three bytes padding
    }; // size: 8, alignment: 4

    printf("alignof(struct X) = %zu\n", alignof(struct X));
    struct X arrX[] = { {1, 'a'}, {2, 'b'}, {3, 'c'} };
    printf("bytes between consecutive elements: %lu, %lu\n", (void*)(arrX + 1) - (void*)arrX, (void*)(arrX + 2) - (void*)(arrX + 1));
    OBJ_REPR(arrX); //01 00 00 00 61 00 00 00 02 00 00 00 62 00 00 00 03 00 00 00 63 00 00 00


    //SIGNED INTEGERS

    //2's complement vs 1's complement
    //(2's complement is the default option in my platform)
    printf("in 2's complement, ~%d = %d\n", 1, ~1); //-2
    printf("in 1's complement, ~%d = %d\n", 1, ~1 + 1); //-1

    //Sign extension: when data type is widened, sign bit is extended to fit new data type
    //This can be problematic if the data type is widened from signed to unsigned type

    //upcasting from short to int
    printf("upcasting from short to int\n");
    short signed_obj1 = -1;
    OBJ_REPR(signed_obj1); //ff ff
    printf("%d\n", signed_obj1); //-1 (2's complement)
    int signed_obj2 = signed_obj1;
    OBJ_REPR(signed_obj2); //ff ff ff ff (sign bit is extended to fit new data type)  
    printf("%d\n", signed_obj2); //-1 (2's complement)

    //upcasting from short to unsigned int
    printf("upcasting from short to unsigned int\n");
    unsigned int signed_obj3 = signed_obj1;
    OBJ_REPR(signed_obj3); //ff ff ff ff (sign bit is extended to fit new data type)
    printf("%u\n", signed_obj3); //4294967295 (2^32 - 1)

}

