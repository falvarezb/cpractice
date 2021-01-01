#ifndef	STRLIBRARY_H
#define	STRLIBRARY_H

/*
    Returns a newly allocated string without blank chars
    If all chars in str are blank, returns NULL
*/
char* strip_blanks(const char* str);

/*
    Returns the newly allocated string str[from:to]
    If from < 0 or to > size(str), returns NULL
*/
char* substring(const char *str, int from, int to);

/*
    Split str into tokens and returns an array of tokens
*/
char** split(char *str, const char *delimiter);


#endif //STRLIBRARY_H