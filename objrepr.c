/**
 *  https://en.cppreference.com/w/c/language/object
 *  
 *  Objects are composed of contiguous sequences of one or more bytes, each byte consisting of CHAR_BIT bits.
 *  CHAR_BIT is platform-dependent (although the most common value is 8)
 * 
 *  Note: to avoid ambiguity, C99 introduces the types int8_t, int16_t, int32_t, and int64_t, 
 *  all have the size (in bits) indicated by their names
 *  
 *  As the language spec establishes that the size of a char is always 1 byte, any object can be represented as
 *  the array char[n], where n is the size of the object.
 * 
 *  Notes: 
 *  - if an object representation does not represent any value of the object type, it is known as trap representation
 *  - when objects of integer types occupy multiple bytes, the use of those bytes is implementation-defined, but the 
 *  two dominant implementations are big-endian and little-endian
 * 
 * 
 * Object representation is also determined by the alignment requirement of each object type. The alignment requirement is a
 * non-negative power of two that represents the number of bytes between successive addresses at which objects of a type
 * can be allocated. Alignment requirements maximise the chances of the CPU fetching the data with one single access to memory
 * as the data will be contained in one word.
 * 
 * In order to satisfy alignment requirements of all members of a struct, padding may be inserted after some of its members
 * Here's the alignment requirements for structs:
 * - data structures are maximally aligned. That is, the address of any instance of a structure (including one in an array) 
 * will be divisible by the size of its largest native integer field.
 * - fields whose type is a multibyte integer type are aligned to their size (in bytes). For instance, an int32_t integer 
 * field’s beginning address is always divisible by four
 **/


#include <stdio.h>
#include <stdalign.h>
#include <arpa/inet.h>

void obj_repr(void* obj, size_t len) {     
    unsigned char* ptr = (unsigned char*) obj;
    for (int i=0; i<len; i++) 
        printf("%.2x ", ptr[i]);
    printf("\n");
}

int main() {
    
    int obj1 = 0x2842;
    long obj2 = 0x2842;


    //MULTI-BYTE INTEGERS

    //Little-endian representation (least significant bytes are stored at the lowest addresses)
    //(little-endian is the default option in my platform)
    printf("Little-endian representation\n");
    obj_repr(&obj1, sizeof(obj1)); //42 28 00 00 -> 4 bytes
    obj_repr(&obj2, sizeof(obj2)); //42 28 00 00 00 00 00 00 -> 8 bytes

    //Big-endian representation
    printf("Big-endian representation\n");
    int obj1_bigend = htonl(obj1);
    long obj2_bigend = htonll(obj2);
    obj_repr(&obj1_bigend, sizeof(obj1)); //00 00 28 42 -> 4 bytes    
    obj_repr(&obj2_bigend, sizeof(obj2)); //00 00 00 00 00 00 28 42 -> 8 bytes    

    obj_repr(&"12345", sizeof("12345")); //31 32 33 34 35 00 -> 6 bytes, including final null byte '\0'

    
    //ALIGNMENT

    printf("alignof(int) %zu\n", alignof(int));

    struct X {
        int n;  // size: 4, alignment: 4
        char c; // size: 1, alignment: 1
        // three bytes padding
    }; // size: 8, alignment: 4

    printf("alignof(struct X) = %zu\n", alignof(struct X));
    struct X arrX[] = {{1, 'a'}, {2, 'b'}, {3, 'c'}};     
    printf("bytes between consecutive elements: %p, %p\n", ((void *) (arrX+1)-(void*) arrX, (void *) (arrX+2)-(void*) (arrX+1)));
    obj_repr(&arrX, sizeof(arrX)); //01 00 00 00 61 00 00 00 02 00 00 00 62 00 00 00 03 00 00 00 63 00 00 00

    
    //SIGNED INTEGERS

    //2's complement vs 1's complement
    //(2's complement is the default option in my platform)
    printf("in 2's complement, ~%d = %d\n", 1, ~1); //-2
    printf("in 1's complement, ~%d = %d\n", 1, ~1+1); //-1

    //Sign extension: when data type is widened, sign bit is extended to fit new data type
    //This can be problematic if the data type is widened from signed to unsigned type

    //upcasting from short to int
    short signed_obj1 = -1;
    obj_repr(&signed_obj1, sizeof(signed_obj1)); //ff ff
    printf("%d\n", signed_obj1); //-1 (2's complement)
    int signed_obj2 = signed_obj1;
    obj_repr(&signed_obj2, sizeof(signed_obj2)); //ff ff ff ff (sign bit is extended to fit new data type)  
    printf("%d\n", signed_obj2); //-1 (2's complement)

    //upcasting from short to unsigned int
    unsigned int signed_obj3 = signed_obj1;
    obj_repr(&signed_obj3, sizeof(signed_obj3)); //ff ff ff ff (sign bit is extended to fit new data type)
    printf("%u\n", signed_obj3); //4294967295 (2^32 - 1)


    //
}

