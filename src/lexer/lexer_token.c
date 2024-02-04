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


    token_t *new_token = create_token(TOKEN_NONE, NULL);


    if      (is_alpha(lexer->current_source_char))
    {

        free(new_token);

        new_token = lexer_parse_id(lexer);

        if (new_token == NULL)
        {

            /* TODO:  */


            exit(EXIT_FAILURE);

        }

        if (token_id_to_keyword_mapping(new_token) == false)
        {

            /* TODO:  */


            exit(EXIT_FAILURE);

        }

    }
    else if (is_digit(lexer->current_source_char))
    {

        free(new_token);

        new_token = lexer_parse_number(lexer);

        if (new_token == NULL)
        {

            /* TODO:  */


            exit(EXIT_FAILURE);

        }

    }
    else
    {

        switch (lexer->current_source_char)
        {

        case '.': new_token->type = TOKEN_DOT  ; break;

        case ',': new_token->type = TOKEN_COMMA; break;

        case ':': new_token->type = TOKEN_COLON; break;

        case ';':

            if (lexer_eat_char(lexer, '#'))
            {

                lexer_skip_line(lexer);

            }
            else
            {

                new_token->type = TOKEN_SEMICOLON;

            }

            break;


        case '=':

            switch (lexer_peek_char(lexer, 1))
            {

            case '=':

                new_token->type = TOKEN_EQUAL       ;

                lexer_next_char(lexer);

                break;

            case '<':

                new_token->type = TOKEN_EQUAL_OR_LES;

                lexer_next_char(lexer);

                break;

            case '>':

                new_token->type = TOKEN_EQUAL_OR_GRE;

                lexer_next_char(lexer);

                break;


            default:

                new_token->type = TOKEN_ASSIGN      ;

                break;

            }

            break;

        case '<':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_LES_OR_EQUAL : TOKEN_LES_THAN;

            break;

        case '>':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_GRE_OR_EQUAL : TOKEN_GRE_THAN;

            break;


        case '(': new_token->type = TOKEN_L_PARENTHESIS; break;

        case ')': new_token->type = TOKEN_R_PARENTHESIS; break;

        case '[': new_token->type = TOKEN_L_BRACKET    ; break;

        case ']': new_token->type = TOKEN_R_BRACKET    ; break;

        case '{': new_token->type = TOKEN_L_BRACE      ; break;

        case '}': new_token->type = TOKEN_R_BRACE      ; break;


        case '-': new_token->type = TOKEN_SUB_SIGNAL; break;

        case '+': new_token->type = TOKEN_ADD_SIGNAL; break;

        case '*': new_token->type = TOKEN_MUL_SIGNAL; break;

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

                new_token->type = TOKEN_DIV_SIGNAL;

                break;

            }

            break;

        default:

            fprintf(stderr, "Error, invalid character for lexer, %%c = %c, %%d = %d.\n", lexer->current_source_char, (int)lexer->current_source_char);


            free_token(new_token);

            new_token = NULL;

            break;

        }

    }


    return new_token;

}
