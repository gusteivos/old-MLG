#include <lexer.h>


token_t *lexer_parse_id(lexer_t *lexer)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return NULL;

    }


    size_t value_size = 2;

    char  *value = malloc(value_size);

    value[0] = lexer->current_source_char;


    char c = '\0';

    while (is_alpha_others(c = lexer_peek_char(lexer, 1)) || is_digit(c))
    {

        lexer_next_char(lexer);

        size_t previous_value_size = value_size++;

        value = safe_realloc(value, value_size);

        if (value == NULL)
        {



            exit(EXIT_FAILURE);

        }

        value[previous_value_size - 1] = lexer->current_source_char;

    }

    value[value_size - 1] = '\0';


    token_t *new_token = create_token(TOKEN_ID, value);

    free(value);

    if (new_token == NULL)
    {

        fprintf(stderr, "TODO: .\n");


        return NULL;

    }


    return new_token;

}
