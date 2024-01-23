#include <lexer.h>


lexer_t *create_lexer(char *source)
{

    if (source == NULL)
    {

        fprintf(stderr ,"Error, creating a lexer, source is NULL.");


        return NULL;

    }


    lexer_t *new_lexer = (lexer_t *)malloc(sizeof(lexer_t));

    if (new_lexer == NULL)
    {

        fprintf(stderr, "Error, allocating memory for a new lexer.\n");


        return NULL;

    }


    new_lexer->source = strdup(source);

    new_lexer->source_size = strlen(new_lexer->source);

    new_lexer->source_index = 0;

    new_lexer->current_source_char = new_lexer->source[new_lexer->source_index];


    return new_lexer;

}


void free_lexer(lexer_t *lexer)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return;

    }


    if (lexer->source != NULL)
    {

        free(lexer->source);

    }


    free(lexer);

}
