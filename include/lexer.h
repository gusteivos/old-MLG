
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


    extern char lexer_next_char  (lexer_t *lexer);

    extern char lexer_peek_char  (lexer_t *lexer, long offset);

    extern bool lexer_eat_char   (lexer_t *lexer, char c);

    extern void lexer_skip_spaces(lexer_t *lexer);

    extern void lexer_skip_line  (lexer_t *lexer);


    extern token_t *lexer_parse_id    (lexer_t *lexer);
    
    extern token_t *lexer_parse_number(lexer_t *lexer);


    extern token_t *lexer_next_token(lexer_t *lexer);


    extern void free_lexer(lexer_t *lexer);

#endif
