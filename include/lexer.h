
#ifndef LEXER_H_
#define LEXER_H_

    #include <token.h>
    #include <utils.h>


    typedef struct lexer_s
    {

        char *source;

        long  source_size;

        long  source_index;

        char current_source_char;

    } lexer_t;


    extern lexer_t *create_lexer(char *source);



    extern void free_lexer(lexer_t *lexer);

#endif
