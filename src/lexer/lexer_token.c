#include <lexer.h>


token_t *lexer_next_token(lexer_t *lexer)
{

    if (lexer == NULL)
    {

        fprintf(stderr, "Error, lexer is NULL.\n");


        return NULL;

    }


    lexer_skip_spaces(lexer);


    if (lexer->current_source_char == '\0')
    {

        return create_token(TOKEN_EOF, NULL);

    }


    token_t *new_token = NULL;


    if      (is_alpha(lexer->current_source_char))
    {

        token_id_to_keyword_mapping(new_token = lexer_parse_id(lexer));

    }
    else if (is_digit(lexer->current_source_char))
    {

        /*TODO: parse number.*/

    }
    else
    {

        switch (lexer->current_source_char)
        {

        case '.': new_token = create_token(TOKEN_DOT      , NULL); break;

        case ',': new_token = create_token(TOKEN_COMMA    , NULL); break;

        case ':': new_token = create_token(TOKEN_COLON    , NULL); break;

        case ';':

            if (lexer_eat_char(lexer, '#'))
            {

                lexer_skip_line(lexer);

            }
            else
            {

                new_token   = create_token(TOKEN_SEMICOLON , NULL);

            }

            break;


        case '=':

            switch (lexer_peek_char(lexer, 1))
            {

            case '=':

                new_token = create_token(TOKEN_EQUAL       , NULL);

                lexer_next_char(lexer);

                break;

            /* For the future maybe:

            case '<':

                new_token = create_token(TOKEN_EQUAL_OR_LES, NULL);

                lexer_next_char(lexer);

                break;

            case '>':

                new_token = create_token(TOKEN_EQUAL_OR_BIG, NULL);

                lexer_next_char(lexer);

                break;

            */


            default:

                new_token = create_token(TOKEN_ASSIGN      , NULL);

                break;

            }

            break;

        case '<':

            if (lexer_eat_char(lexer, '='))
            {

                new_token = create_token(TOKEN_LES_OR_EQUAL, NULL);

            }
            else
            {

                new_token = create_token(TOKEN_LES_THAN    , NULL);

            }

            break;

        case '>':

            if (lexer_eat_char(lexer, '='))
            {

                new_token = create_token(TOKEN_BIG_OR_EQUAL, NULL);

            }
            else
            {

                new_token = create_token(TOKEN_BIG_THAN    , NULL);

            }

            break;


        case '(': new_token = create_token(TOKEN_L_PARENTHESIS, NULL); break;

        case ')': new_token = create_token(TOKEN_R_PARENTHESIS, NULL); break;

        case '[': new_token = create_token(TOKEN_L_BRACKET    , NULL); break;

        case ']': new_token = create_token(TOKEN_R_BRACKET    , NULL); break;

        case '{': new_token = create_token(TOKEN_L_BRACE      , NULL); break;

        case '}': new_token = create_token(TOKEN_R_BRACE      , NULL); break;


        case '-': new_token = create_token(TOKEN_SUB, NULL); break;

        case '+': new_token = create_token(TOKEN_SUM, NULL); break;

        case '*': new_token = create_token(TOKEN_MUL, NULL); break;

        case '/':

            switch (lexer_peek_char(lexer, 1))
            {

            case '/':

                lexer_next_char(lexer);

                lexer_skip_line(lexer);


                break;


            case '*':

                lexer_next_char(lexer);

                lexer_next_char(lexer);


                while (lexer->current_source_char != '\0')
                {

                    if (lexer->current_source_char == '*')
                    {

                        if (lexer_eat_char(lexer, '/'))
                        {

                            break;

                        }

                    }


                    lexer_next_char(lexer);

                }

                break;


            default:

                new_token = create_token(TOKEN_DIV, NULL);


                break;

            }

            break;

        default:

            fprintf(stderr, "Error, invalid character for lexer, %%c = %c, %%d = %d.\n", lexer->current_source_char, (int)lexer->current_source_char);

            break;

        }

    }


    return new_token;

}
