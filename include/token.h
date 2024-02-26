
#ifndef TOKEN_H_
#define TOKEN_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>


    typedef enum token_type_e
    {
        
        TOKEN_NONE = 0,
        
        TOKEN_KEYWORD_NONE,
        
        TOKEN_KEYWORD_T_INT8 ,
        TOKEN_KEYWORD_T_INT16,
        TOKEN_KEYWORD_T_INT32,
        TOKEN_KEYWORD_T_INT64,

        TOKEN_KEYWORD_FUNCTION,
        
        TOKEN_KEYWORD_RETURN,
        TOKEN_KEYWORD_IF    ,
        TOKEN_KEYWORD_ELSE  ,
        TOKEN_KEYWORD_LOOP  ,
        TOKEN_KEYWORD_WHILE ,
        TOKEN_KEYWORD_FOR   ,
        TOKEN_KEYWORD_BREAK ,

        TOKEN_ID,

        TOKEN_LITERAL_NUMBER,

        TOKEN_DOT      ,
        TOKEN_COMMA    ,
        TOKEN_COLON    ,
        TOKEN_SEMICOLON,

        TOKEN_PLUS    , /* + */
        TOKEN_MINUS   , /* - */
        TOKEN_ASTERISK, /* * */
        TOKEN_SLASH   , /* / */
        TOKEN_PERCENT , /* % */

        TOKEN_AMPERSAND , /* &  */
        TOKEN_PIPE      , /* |  */
        TOEKN_CIRCUMFLEX, /* ^  */
        TOKEN_L_SHIFT   , /* << */
        TOKEN_R_SHIFT   , /* >> */
        TOKEN_TIL       , /* ~  */
        
        TOKEN_AND        , /* && */
        TOKEN_OR         , /* || */
        TOKEN_EXCLAMATION, /* !  */

        TOKEN_ASSIGN, /* = */

        TOKEN_PLUS_ASSIGN , /* += */
        TOKEN_MINUS_ASSIGN, /* -= */
        TOKEN_MUL_ASSIGN  , /* *= */
        TOKEN_DIV_ASSIGN  , /* /= */
        TOKEN_MOD_ASSIGN  , /* %= */

        TOKEN_AND_ASSIGN    , /* &=  */
        TOKEN_OR_ASSIGN     , /* |=  */
        TOKEN_XOR_ASSIGN    , /* ^=  */
        TOKEN_L_SHIFT_ASSIGN, /* <<= */
        TOKEN_R_SHIFT_ASSIGN, /* >>= */
        
        TOKEN_LES_THAN    , /* <  */
        TOKEN_LES_OR_EQUAL, /* <= */
        TOKEN_GRE_THAN    , /* >  */
        TOKEN_GRE_OR_EQUAL, /* >= */
        TOKEN_EQUAL       , /* == */
        TOKEN_NOT_EQUAL   , /* != */

        TOKEN_AT, /* @ */

        TOKEN_L_PAREN  , /* ( */
        TOKEN_R_PAREN  , /* ) */
        TOKEN_L_BRACKET, /* [ */
        TOKEN_R_BRACKET, /* ] */
        TOKEN_L_BRACE  , /* { */
        TOKEN_R_BRACE  , /* } */

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
