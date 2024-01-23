
#ifndef TOKEN_H_
#define TOKEN_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>


    typedef enum token_type_e
    {

        TOKEN_NONE = 0,

        TOKEN_KEYWORD_FUNC,

        TOKEN_EOF  = EOF

    } token_type_t;

    typedef struct token_s
    {

        token_type_t type;

        char *value;

    } token_t;

    typedef struct token_mapping_s
    {

        char *value0;

        char *value1;

        token_type_t type;

    } token_mapping_t;


    extern token_mapping_t token_keyword_mappings[];


    extern token_t *create_token(token_type_t type, char *value);


    extern void free_token(token_t *token);


    extern bool token_to_mapping(token_t *token, token_mapping_t *mappings, bool free_token_value);

#endif
