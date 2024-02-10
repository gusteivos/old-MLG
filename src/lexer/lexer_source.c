#include <lexer.h>


char lexer_next_char(lexer_t *lexer)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return '\0';

    }


    if (lexer->current_source_char != '\0' && lexer->source_index < lexer->source_size)
    {

        lexer->source_index++;

    }


    return lexer->current_source_char = lexer->source[lexer->source_index];

}

char lexer_peek_char(lexer_t *lexer, long offset)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return '\0';

    }


    long index = lexer->source_index + offset;

    if (index < 0 || index > lexer->source_size)
    {

        return '\0';

    }


    return lexer->source[index];

}

bool lexer_eat_char(lexer_t *lexer, char c)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return false;

    }


    if (lexer_peek_char(lexer, 1) == c)
    {

        lexer_next_char(lexer);


        return true;

    }


    return false;

}

void lexer_skip_spaces(lexer_t *lexer)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return;

    }


    while (lexer->current_source_char != '\0' && strchr(" \t\r\n", lexer->current_source_char))
    {

        if (lexer_next_char(lexer) == '\0')
        {
        
            return;
        
        }

    }

}

void lexer_skip_line(lexer_t *lexer)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return;

    }


    while (lexer->current_source_char != '\0' && lexer->current_source_char != '\n')
    {

        lexer_skip_spaces(lexer);

        lexer_next_char  (lexer);

    }
    
}