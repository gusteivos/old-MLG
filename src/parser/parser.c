#include <parser.h>


parser_t *create_parser(list_t *token_list)
{

    if (token_list == NULL)
    {

        fprintf(stderr, "Error: token_list is NULL.\n");


        return NULL;

    }


    parser_t *new_parser = (parser_t *)malloc(sizeof(parser_t));

    if (new_parser == NULL)
    {

        fprintf(stderr, "Error: allocating memory for a new parser.\n");


        return NULL;

    }


    new_parser->token_list = token_list;

    new_parser->token_index = 0;


    new_parser->current_token = (token_t *)list_get_by_index(new_parser->token_list, new_parser->token_index);


    return new_parser;

}

operator_t parser_token_type_to_binary_operator(token_type_t type)
{


    switch (type)
    {

    case TOKEN_PLUS: return OPERATOR_ARITHMETIC_ADD;

    case TOKEN_MINUS: return OPERATOR_ARITHMETIC_SUB;
    
    case TOKEN_ASTERISK: return OPERATOR_ARITHMETIC_MUL;
    
    case TOKEN_SLASH: return OPERATOR_ARITHMETIC_DIV;

    case TOKEN_PERCENT: return OPERATOR_ARITHMETIC_MOD;


    default: return  DATA_TYPE_NONE;
    
    }


}

data_type_type_t parser_token_type_to_data_type_type(token_type_t type)
{

    switch (type)
    {

    case TOKEN_KEYWORD_T_INT8 : return DATA_TYPE_INT8 ;

    case TOKEN_KEYWORD_T_INT16: return DATA_TYPE_INT16;

    case TOKEN_KEYWORD_T_INT32: return DATA_TYPE_INT32;

    case TOKEN_KEYWORD_T_INT64: return DATA_TYPE_INT64;


    default: return  DATA_TYPE_NONE;

    }

}


void free_parser(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return;

    }


    /* TODO: */


    free(parser);

}
