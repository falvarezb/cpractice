#include "acutest.h"
#include "bigint.h"
#include <stddef.h>
#include <math.h>
#include <string.h>

void test_from_to_string() 
{
    {
        char* str = "000000000000000123";
        uint64_t expected[] = {123};
        struct bigint result = from_string(str);
        char* result2 = to_string(result);
        TEST_CHECK_(result.number[0] == expected[0], "from_string(%s)[0]=%llu but expected %llu", str, result.number[0], expected[0]);
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }

    {
        char* str = "000000000000000012345678901234567899";
        uint64_t expected[] = {345678901234567899, 12};
        struct bigint result = from_string(str);
        char* result2 = to_string(result);
        TEST_CHECK_(result.number[0] == expected[0], "from_string(%s)[0]=%llu but expected %llu", str, result.number[0], expected[0]);
        TEST_CHECK_(result.number[1] == expected[1], "from_string(%s)[1]=%llu but expected %llu", str, result.number[1], expected[1]);  
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }

    {
        char* str = "123456789012345678";
        uint64_t expected[] = {123456789012345678};
        struct bigint result = from_string(str);
        char* result2 = to_string(result);
        TEST_CHECK_(result.number[0] == expected[0], "from_string(%s)[0]=%llu but expected %llu", str, result.number[0], expected[0]);         
        TEST_CHECK_(strcmp(result2, str) == 0, "result %s but expected %s", result2, str);    
    }
}

void test_to_from_string() 
{
    {
        char* expected = "000000000000000123";
        uint64_t number[] = {123};
        struct bigint bigint = {number, 1};
        char* result = to_string(bigint);
        struct bigint result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2.number[0] == bigint.number[0], "result %llu but expected %llu", result2.number[0], bigint.number[0]);    
    }

    {
        char* expected = "000000000000000012345678901234567899";
        uint64_t number[] = {345678901234567899, 12};
        struct bigint bigint = {number, 2};
        char* result = to_string(bigint);
        struct bigint result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2.number[0] == bigint.number[0], "result %llu but expected %llu", result2.number[0], bigint.number[0]);   
        TEST_CHECK_(result2.number[1] == bigint.number[1], "result %llu but expected %llu", result2.number[1], bigint.number[1]);  
    }

    {
        char* expected = "123456789012345678";
        uint64_t number[] = {123456789012345678};
        struct bigint bigint  = {number, 1};
        char* result = to_string(bigint);
        struct bigint result2 = from_string(result);
        
        TEST_CHECK_(strcmp(result, expected) == 0, "to_string()=%s but expected %s", result, expected);
        TEST_CHECK_(result2.number[0] == bigint.number[0], "result %llu but expected %llu", result2.number[0], bigint.number[0]);
    }
}

void test_sum() 
{
    {
        uint64_t u[] = {1};
        uint64_t v[] = {2};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits+1];
        sum(num_digits, u, v, result);
        uint64_t expected[] = {3};
        TEST_CHECK_(result[0] == expected[0], "sum()[0]=%llu but expected %llu", result[0], expected[0]);
    }

    {
        uint64_t u[] = {123456789012345678lu, 576839484849498888lu};
        uint64_t v[] = {987654321098765432lu, 974857487482847488lu};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits+1];
        sum(num_digits, u, v, result);
        uint64_t expected[] = {111111110111111110, 551696972332346377, 1};
        TEST_CHECK_(result[0] == expected[0], "sum()[0]=%llu but expected %llu", result[0], expected[0]);
        TEST_CHECK_(result[1] == expected[1], "sum()[0]=%llu but expected %llu", result[1], expected[1]);
        TEST_CHECK_(result[2] == expected[2], "sum()[0]=%llu but expected %llu", result[2], expected[2]);
    }
}

void test_subtract() 
{
    {
        uint64_t u[] = {3};
        uint64_t v[] = {1};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits];
        subtract(num_digits, u, v, result);
        uint64_t expected[] = {2};
        TEST_CHECK_(result[0] == expected[0], "subtract()[0]=%llu but expected %llu", result[0], expected[0]);
    }

    {
        uint64_t u[] = {3};
        uint64_t v[] = {3};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits];
        subtract(num_digits, u, v, result);
        uint64_t expected[] = {0};
        TEST_CHECK_(result[0] == expected[0], "subtract()[0]=%llu but expected %llu", result[0], expected[0]);
    }

    {
        uint64_t u[] = {123456789012345678lu, 576839484849498888lu};
        uint64_t v[] = {987654321098765432lu, 174857487482847488lu};
        int num_digits = fmax(sizeof(u)/sizeof(u[0]), sizeof(v)/sizeof(v[0]));
        uint64_t result[num_digits];
        subtract(num_digits, u, v, result);
        uint64_t expected[] = {135802467913580246, 401981997366651399};
        TEST_CHECK_(result[0] == expected[0], "subtract()[0]=%llu but expected %llu", result[0], expected[0]);
        TEST_CHECK_(result[1] == expected[1], "subtract()[1]=%llu but expected %llu", result[1], expected[1]);
    }
}

void test_bigsum(){
    {
        char* a = "125858548944446868589689484398988889";
        char* b= "4404588898938984849498448948989";
        char* expected = "125862953533345807574538982847937878";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "-1";
        char* b= "12";
        char* expected = "13";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "0";
        char* b= "0";
        char* expected = "0";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1";
        char* b= "1843947378473748483873478";
        char* expected = "1843947378473748483873479";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1843947378473748483873478";
        char* b= "1";
        char* expected = "1843947378473748483873479";
        char* result = bigsum(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }
}

void test_bigsubtract(){
    {
        char* a = "125858548944446868589689484398988889";
        char* b= "4404588898938984849498448948989";
        char* expected = "125854144355547929604839985950039900";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsubtract(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1";
        char* b= "12";
        char* expected = "-11";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsubtract(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "12";
        char* b= "12";
        char* expected = "0";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsubtract(%s, %s)=%s but expected %s", a, b, result, expected);
    }

     {
        char* a = "1";
        char* b= "1843947378473748483873478";
        char* expected = "-1843947378473748483873477";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }

    {
        char* a = "1843947378473748483873478";
        char* b= "1";
        char* expected = "1843947378473748483873477";
        char* result = bigsubtract(a, b);
        TEST_CHECK_(strcmp(result, expected) == 0, "bigsum(%s, %s)=%s but expected %s", a, b, result, expected);
    }
}

TEST_LIST = {
    {"test_from_to_string", test_from_to_string},
    {"test_to_from_string", test_to_from_string},
    {"test_sum", test_sum},
    {"test_subtract", test_subtract},
    {"test_bigsum", test_bigsum},
    {"test_bigsubtract", test_bigsubtract}
};
