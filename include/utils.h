
#ifndef UTILS_H_
#define UTILS_H_

    #include <ctype.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>


    extern char alpha_others[];
    
    extern char digit_others[];


    extern bool is_alpha(char c);

    extern bool is_digit(char c);

    extern bool is_alpha_or_others(char c, char *others);
    
    extern bool is_digit_or_others(char c, char *others);


    extern void *safe_realloc(void *ptr, size_t new_size);


    #define is_alpha_others(c) is_alpha_or_others(c, alpha_others)

    #define is_digit_others(c) is_digit_or_others(c, digit_others)

#endif
