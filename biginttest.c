#include "acutest.h"
#include "bigint.h"
#include <stddef.h>
#include <math.h>
#include <string.h>

void test_from_to_string() 
{
    {
        char* str = "000000000000000123";
        size_t expected[] = {123};
        size_t* result = from_string(str);
        char* result2 = to_string(result, 1);
        TEST_CHECK_(result[0] == expected[0], "from_string(%s)[0]=%lu but expected %lu", str, result[0], expected[0]);
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }

    {
        char* str = "000000000000000012345678901234567899";
        size_t expected[] = {345678901234567899, 12};
        size_t* result = from_string(str);
        char* result2 = to_string(result, 2);
        TEST_CHECK_(result[0] == expected[0], "from_string(%s)[0]=%lu but expected %lu", str, result[0], expected[0]);
        TEST_CHECK_(result[1] == expected[1], "from_string(%s)[1]=%lu but expected %lu", str, result[1], expected[1]);  
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }

    {
        char* str = "123456789012345678";
        size_t expected[] = {123456789012345678};
        size_t* result = from_string(str);
        char* result2 = to_string(result, 1);
        TEST_CHECK_(result[0] == expected[0], "from_string(%s)[0]=%lu but expected %lu", str, result[0], expected[0]);         
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }
}

void test_to_from_string() 
{
    {
        char* expected = "000000000000000123";
        size_t bigint[] = {123};
        char* result = to_string(bigint, 1);
        size_t* result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2[0] == bigint[0], "result %lu but expected %lu", result2[0], bigint[0]);    
    }

    {
        char* expected = "000000000000000012345678901234567899";
        size_t bigint[] = {345678901234567899, 12};
        char* result = to_string(bigint, 2);
        size_t* result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2[0] == bigint[0], "result %lu but expected %lu", result2[0], bigint[0]);   
        TEST_CHECK_(result2[1] == bigint[1], "result %lu but expected %lu", result2[1], bigint[1]);  
    }

    {
        char* expected = "123456789012345678";
        size_t bigint[] = {123456789012345678};
        char* result = to_string(bigint, 1);
        size_t* result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2[0] == bigint[0], "result %lu but expected %lu", result2[0], bigint[0]);
    }
}

void test_sum() 
{
    {
        size_t u[] = {1};
        size_t v[] = {2};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        size_t result[num_digits+1];
        sum(num_digits, u, v, result);
        size_t expected[] = {3};
        TEST_CHECK_(result[0] == expected[0], "sum()[0]=%lu but expected %lu", result[0], expected[0]);
    }

    {
        size_t u[] = {123456789012345678lu, 576839484849498888lu};
        size_t v[] = {987654321098765432lu, 974857487482847488lu};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        size_t result[num_digits+1];
        sum(num_digits, u, v, result);
        size_t expected[] = {111111110111111110, 551696972332346377, 1};
        TEST_CHECK_(result[0] == expected[0], "sum()[0]=%lu but expected %lu", result[0], expected[0]);
        TEST_CHECK_(result[1] == expected[1], "sum()[0]=%lu but expected %lu", result[1], expected[1]);
        TEST_CHECK_(result[2] == expected[2], "sum()[0]=%lu but expected %lu", result[2], expected[2]);
    }
}


TEST_LIST = {
    {"test_from_to_string", test_from_to_string},
    {"test_to_from_string", test_to_from_string},
    {"test_sum", test_sum}
};
