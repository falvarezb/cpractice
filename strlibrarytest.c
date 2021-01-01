#include <stdio.h>
#include "acutest.h"
#include "strlibrary.h"

void test_strip_blanks() {
    {
        const char *str = "  ";
        const char *expected = NULL;
        char *binary_instruction = strip_blanks(str);
        TEST_CHECK_(binary_instruction  == expected, "strip_comments(%s)=%s but expected %s", str, binary_instruction, expected);      
    }

    {
        const char *str = " x x x ";
        const char *expected = "xxx";
        char *binary_instruction = strip_blanks(str);
        TEST_CHECK_(strcmp(binary_instruction, expected) == 0, "strip_comments(%s)=%s but expected %s", str, binary_instruction, expected);      
    }
}

void test_substring() {
    {
        char *result = substring("hello", 0, 2);
        char *expected = "he";         
        TEST_CHECK_(strcmp(result, expected) == 0, "substring(%s,%d,%d)==%s but expected %s", "hello", 0, 2, result, expected);
    }

    {
        char *result = substring("hello", 1, 3);
        char *expected = "el"; 
        TEST_CHECK_(strcmp(result, expected) == 0, "substring(%s,%d,%d)==%s but expected %s", "hello", 1, 3, result, expected);
    }

    {
        char *result = substring("hello", 1, 10);
        char *expected = NULL; 
        TEST_CHECK_(result == expected, "substring(%s,%d,%d)==%s but expected %s", "hello", 1, 10, result, expected);
    }
}

void test_split_helper(int idx, char *expected[], char *result[], char *str, const char *delimiter) {
    TEST_CHECK_(strcmp(result[idx], expected[idx]) == 0, "split(%s,'%s')[%d]==%s but expected %s", str, delimiter, idx, result[idx], expected[idx]);
}

void test_split() {
    {        
        char str[] = "he,llo";
        const char *delimiters = ",";        
        char **result = split(str, delimiters);
        char *expected[] = {"he","llo"};    
        test_split_helper(0, expected, result, str, delimiters);
        test_split_helper(1, expected, result, str, delimiters);        
    }

    {        
        char str[] = "hello";
        const char *delimiters = ",";        
        char **result = split(str, delimiters);
        char *expected[] = {"hello"};    
        test_split_helper(0, expected, result, str, delimiters);    
    }

    {
        char str[] = "hello there world";
        char *delimiters = " ";
        char **result = split(str, delimiters);
        char *expected[] = {"hello", "there", "world"};    
        test_split_helper(0, expected, result, str, delimiters);
        test_split_helper(1, expected, result, str, delimiters); 
        test_split_helper(2, expected, result, str, delimiters);        
    }
}

TEST_LIST = {
    {"test_strip_blanks", test_strip_blanks},
    {"test_substring", test_substring},
    {"test_split", test_split}
};
