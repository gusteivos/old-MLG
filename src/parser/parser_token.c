#include <parser.h>


token_t *parser_next_token(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    if (parser->current_token->type != TOKEN_EOF && parser->token_index < parser->token_list->count)
    {

        parser->token_index++;

    }


    return parser->current_token = list_get_by_index(parser->token_list, parser->token_index);

}

token_t *parser_peek_token(parser_t *parser, int offset)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    int index = parser->token_index + offset;


    index = (index < 0) ? 0 : index;

    index = (index >= parser->token_list->count) ? parser->token_list->count - 1 : index;


    return list_get_by_index(parser->token_list, index);

}

bool parser_eat_token(parser_t *parser, token_type_t type, bool can_exit)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return false;

    }


    token_t *peeked_token = parser_peek_token(parser, 1);

    if (peeked_token->type == type)
    {

        parser_next_token(parser);


        return true;

    }
    else if (can_exit)
    {

        fprintf(stderr, "Unexpected token type: %d, with value: %s, when eating the expected token type: %d.\n", peeked_token->type, peeked_token->value, type);


        exit(EXIT_FAILURE);

    }


    return false;

}

bool parser_consume_token(parser_t *parser, token_type_t type, bool can_exit)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return false;

    }


    if (parser->current_token->type == type)
    {

        parser_next_token(parser);


        return true;

    }
    else if (can_exit)
    {

        fprintf(stderr, "Unexpected token type: %d, with value: %s, when consuming the expected token type: %d.\n", parser->current_token->type, parser->current_token->value, type);


        exit(EXIT_FAILURE);

    }


    return false;

}
