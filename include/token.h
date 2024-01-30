
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

        TOKEN_KEYWORD_NONE,
        
        TOKEN_KEYWORD_T_BYTE   ,
        TOKEN_KEYWORD_T_SHORT  ,
        TOKEN_KEYWORD_T_INTEGER,
        TOKEN_KEYWORD_T_LONG   ,

        TOKEN_ID,

        TOKEN_DOT      ,
        TOKEN_COMMA    ,
        TOKEN_COLON    ,
        TOKEN_SEMICOLON,

        TOKEN_ASSIGN      , // =
        TOKEN_EQUAL       , // ==
        TOKEN_EQUAL_OR_GRE, // =<
        TOKEN_EQUAL_OR_LES, // =>
        TOKEN_LES_THAN    , // <
        TOKEN_GRE_THAN    , // >
        TOKEN_LES_OR_EQUAL, // <=
        TOKEN_GRE_OR_EQUAL, // >=

        TOKEN_L_PARENTHESIS, // (
        TOKEN_R_PARENTHESIS, // )
        TOKEN_L_BRACKET    , // [
        TOKEN_R_BRACKET    , // ]
        TOKEN_L_BRACE      , // {
        TOKEN_R_BRACE      , // }

        MLG_TOKEN_ADD_SIGNAL,
        MLG_TOKEN_SUB_SIGNAL,
        MLG_TOKEN_MUL_SIGNAL,
        MLG_TOKEN_DIV_SIGNAL,

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


    extern bool set_token(token_t *token, token_type_t type, char *value);


    extern void free_token(token_t *token);


    extern bool token_to_mapping(token_t *token, token_mapping_t *mappings, bool free_token_value);

    extern bool token_id_to_keyword_mapping(token_t *token);

#endif
