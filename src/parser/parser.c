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
