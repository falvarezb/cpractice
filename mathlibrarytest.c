#include "acutest.h"
#include "mathlibrary.h"

void test_fib() {
    {
        int n = 0;
        int expected = 0;
        int result = fib(n);
        TEST_CHECK_(result  == expected, "fib(%d)=%d but expected %d", n, result, expected);      
    }

    {
        int n = 1;
        int expected = 1;
        int result = fib(n);
        TEST_CHECK_(result  == expected, "fib(%d)=%d but expected %d", n, result, expected);
    }

    {
        int n = 6;
        int expected = 8;
        int result = fib(n);
        TEST_CHECK_(result  == expected, "fib(%d)=%d but expected %d", n, result, expected);
    }
}

void test_bin4(void) {
    int size = 4;
    {
        int n = 0;        
        char* expected = "0000";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    } 

    {
        int n = 2;        
        char* expected = "0010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        //positive overflow
        int n = 10;        
        char* expected = NULL;        
        char* result = bin(n, size);
        TEST_CHECK_(result == expected, "bin(%d,%d)=%s but expected %s", n, size, result, expected);  
    }

    {
        //negative overflow
        int n = -10;        
        char* expected = NULL;        
        char* result = bin(n, size);
        TEST_CHECK_(result == expected, "bin(%d,%d)=%s but expected %s", n, size, result, expected);  
    }

    {
        int n = -1;        
        char* expected = "1111";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected);  
    }
}


void test_bin16(void) {
    int size = 16;
    {
        int n = 0;        
        char* expected = "0000000000000000";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    } 

    {
        int n = 2;        
        char* expected = "0000000000000010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 10;        
        char* expected = "0000000000001010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = -1;        
        char* expected = "1111111111111111";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }
}

void test_bin31(void) {
    int size = 31;
    {
        int n = 0;        
        char* expected = "0000000000000000000000000000000";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    } 

    {
        int n = 2;        
        char* expected = "0000000000000000000000000000010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 10;        
        char* expected = "0000000000000000000000000001010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 1073741823; //2^30 - 1, greatest positive number in 2's complement 31-bit  
        char* expected = "0111111111111111111111111111111";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 1073741824; //2^30, outside range
        char* expected = NULL;        
        char* result = bin(n, size);
        TEST_CHECK_(result == expected, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }
    
    {
        int n = -1;        
        char* expected = "1111111111111111111111111111111";   
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = -1073741824; //-2^30, least negative number in 2's complement 31-bit    
        char* expected = "1000000000000000000000000000000";   
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = -1073741825;  // -2^30 - 1, outside range 
        char* expected = NULL;   
        char* result = bin(n, size);
        TEST_CHECK_(result == expected, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }
}

void test_bin32(void) {
    int size = 32;
    {
        int n = 0;        
        char* expected = "00000000000000000000000000000000";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    } 

    {
        int n = 2;        
        char* expected = "00000000000000000000000000000010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 10;        
        char* expected = "00000000000000000000000000001010";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 2147483647; //2^31 - 1, greatest positive number in 2's complement 32-bit   
        char* expected = "01111111111111111111111111111111";        
        char* result = bin(n, size);
        TEST_CHECK_(strcmp(result, expected) == 0, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    {
        int n = 2147483648; //2^31, outside range  (actually, n is assigned the value -2^31 !!) 
        char* expected = NULL;        
        char* result = bin(n, size);
        TEST_CHECK_(result == expected, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }

    //negative numbers cannot be represented as positive values with the data type int
    {
        int n = -1;        
        char* expected = NULL;   
        char* result = bin(n, size);
        TEST_CHECK_(result == expected, "bin(%d,%d)=%s but expected %s", n, size, result, expected); 
    }
}

void test_count_digits() {
    {
        int n = 0;
        int expected = 1;
        int result = count_digits(n);
        TEST_CHECK_(result  == expected, "count_digits(%d)=%d but expected %d", n, result, expected);      
    }

    {
        int n = 11;
        int expected = 2;
        int result = count_digits(n);
        TEST_CHECK_(result  == expected, "count_digits(%d)=%d but expected %d", n, result, expected); 
    }

    {
        int n = 230;
        int expected = 3;
        int result = count_digits(n);
        TEST_CHECK_(result  == expected, "count_digits(%d)=%d but expected %d", n, result, expected); 
    }
}


TEST_LIST = {
    {"test_fib", test_fib},
    {"test_bin4", test_bin4},
    {"test_bin16", test_bin16},
    {"test_bin31", test_bin31},
    {"test_bin32", test_bin32},
    {"test_count_digits", test_count_digits}
};
