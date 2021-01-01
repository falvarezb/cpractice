#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strlibrary.h"


char* strip_blanks(const char* str) {
    size_t str_without_blanks_upper_bound_size = strlen(str)+1;
    char *str_without_blanks = (char *) malloc(str_without_blanks_upper_bound_size * sizeof(char));
    if(str_without_blanks != NULL) {   
        int char_counter = 0;
        int non_blanks_counter = 0;
        char char_value;
        while((char_value = str[char_counter++]) != '\0'){
            if(char_value != ' '){            
                str_without_blanks[non_blanks_counter++] = char_value;
            }
        }

        if(non_blanks_counter == 0) {
            free(str_without_blanks);
            return NULL;
        }

        str_without_blanks[non_blanks_counter] = '\0';

        size_t str_without_blanks_real_size = strlen(str_without_blanks)+1;
        str_without_blanks = realloc(str_without_blanks, str_without_blanks_real_size * sizeof(char));
    }
    
    return str_without_blanks;
}

char* substring(const char *str, int from, int to) {

    if(from < 0 || to > strlen(str)) {
        return NULL;
    }

    char *substr = (char *) malloc(((to - from) +1) * sizeof(char));
    if(substr != NULL)
        return strncpy(substr, str + from, (to - from));    
    return substr;
}

/*
    Implementation notes:
    - str must be char[] for strtok to work
    - the compiler rewrites char[] param to char*, so we may as well write directly char*
    - <const char*> is used to mean <char *str = "string constant"> as char* is const by default (the array of characters pointed to cannot be modified)
    - <char*> is used to mean <char[]> as the array of characters is expected to be modifiable
*/
char** split(char *str, const char* delimiters) {
    size_t token_list_upper_bound_size = strlen(str);
    size_t num_tokens = 0;
    char **tokens = (char **) malloc(token_list_upper_bound_size * sizeof(char*));
    if(tokens != NULL) {
        char *pch;
        pch = strtok(str, delimiters);    
        while(pch != NULL) {
            tokens[num_tokens++] = pch;
            pch = strtok(NULL, delimiters);
        }
    }

    return tokens;
}



