# C examples


## Object representation

In general, the representation of C objects is platform-dependent. This section describes some of the main factors that determine how objects are represented. 

For more details, see [object representation](https://en.cppreference.com/w/c/language/object).

Check [objrepr.c](https://github.com/falvarezb/cpractice/blob/main/objrepr.c) for some examples.

**Note**: the fact that object representation varies from platform to platform results in the need to define protocols to exchange information between different hosts when communicating over a network

### Objects as arrays of *char*

Objects are composed of contiguous sequences of one or more bytes, each byte consisting of CHAR_BIT bits.
CHAR_BIT is platform-dependent (although the most common value is 8)

**Note**: to avoid ambiguity, C99 introduces the types *int8_t*, *int16_t*, *int32_t*, and *int64_t*, 
all of which have the size (in bits) indicated by their names

As the language spec establishes that the size of a *char* is always 1 byte, any object can be represented as
the array *char[n]*, where n is the size of the object.

**Notes**: 
- if an object representation does not represent any value of the object type, it is known as *trap representation*
- when objects of integer types occupy multiple bytes, the use of those bytes is implementation-defined, but the two dominant implementations are big-endian and little-endian
      

### Alignment requirements

Object representation is also determined by the alignment requirement of each object type. 

The alignment requirement is a non-negative power of two that represents the number of bytes between successive addresses at which objects of a type can be allocated. 

Alignment requirements maximise the chances of the CPU fetching the data with one single access to memory as the data will be contained in one word.
    
In order to satisfy alignment requirements of all members of a struct, padding may be inserted after some of its members

Here's the alignment requirements for structs:

- data structures are maximally aligned, that is, the address of any instance of a structure (including one in an array) will be divisible by the size of its largest native integer field.
   
- fields whose type is a multibyte integer type are aligned to their size (in bytes). For instance, an *int32_t* integer field’s beginning address is always divisible by four
 

### Sign extension

When a data type is widened, sign bit is extended to fit the new data type

This can be problematic if the data type is widened from signed to unsigned type


