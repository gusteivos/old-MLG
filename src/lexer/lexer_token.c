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


        case '+':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_PLUS_ASSIGN  : TOKEN_PLUS    ;

            break;

        case '-':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_MINUS_ASSIGN : TOKEN_MINUS   ;

            break;

        case '*':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_MUL_ASSIGN   : TOKEN_ASTERISK;

            break;

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

            case '=':

                new_token->type = TOKEN_DIV_ASSIGN;

                lexer_next_char(lexer);

                break;


            default:

                new_token->type = TOKEN_SLASH;

                break;

            }

            break;

        case '%':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_MOD_ASSIGN   : TOKEN_PERCENT ;

            break;


        case '&':

            switch (lexer_peek_char(lexer, 1))
            {

            case '=':

                new_token->type = TOKEN_AND_ASSIGN;

                lexer_next_char(lexer);
                
                break;
            
            case '&':

                lexer_next_char(lexer);

                new_token->type = TOKEN_AND;

                break;
            

            default:
            
                new_token->type = TOKEN_AMPERSAND;

                break;
            
            }

            break;

        case '|':

            switch (lexer_peek_char(lexer, 1))
            {

            case '=':

                new_token->type = TOKEN_OR_ASSIGN ;

                lexer_next_char(lexer);
                
                break;
            
            case '|':

                lexer_next_char(lexer);

                new_token->type = TOKEN_OR ;

                break;
            

            default:
            
                new_token->type = TOKEN_PIPE     ;

                break;
            
            }

            break;

        case '^':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_XOR_ASSIGN  : TOEKN_CIRCUMFLEX;

            break;

        case '~':

            new_token->type = TOKEN_TIL;

            break;

        case '!':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_NOT_EQUAL : TOKEN_EXCLAMATION;
            
            break;


        case '<':

            switch (lexer_peek_char(lexer, 1))
            {

            case '=':

                new_token->type = TOKEN_LES_OR_EQUAL;

                lexer_next_char(lexer);
                
                break;
            
            case '<':

                lexer_next_char(lexer);

                new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_L_SHIFT_ASSIGN : TOKEN_L_SHIFT;

                break;
            

            default:
            
                new_token->type = TOKEN_LES_THAN;

                break;
            
            }

            break;

        case '>':

            switch (lexer_peek_char(lexer, 1))
            {

            case '=':
                
                new_token->type = TOKEN_GRE_OR_EQUAL;

                lexer_next_char(lexer);

                break;
            
            case '>':

                lexer_next_char(lexer);

                new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_R_SHIFT_ASSIGN : TOKEN_R_SHIFT;

                break;
            

            default:
            
                new_token->type = TOKEN_GRE_THAN;

                break;
            
            }

            break;
        
        case '=':

            new_token->type = lexer_eat_char(lexer, '=') ? TOKEN_EQUAL : TOKEN_ASSIGN;
            
            break;


        case '@':

            new_token->type = TOKEN_AT;

            break;


        case '(': new_token->type = TOKEN_L_PAREN  ; break;

        case ')': new_token->type = TOKEN_R_PAREN  ; break;

        case '[': new_token->type = TOKEN_L_BRACKET; break;

        case ']': new_token->type = TOKEN_R_BRACKET; break;

        case '{': new_token->type = TOKEN_L_BRACE  ; break;

        case '}': new_token->type = TOKEN_R_BRACE  ; break;


        default:

            fprintf(stderr, "Error, invalid character for lexer, %%c = %c, %%d = %d.\n", lexer->current_source_char, (int)lexer->current_source_char);


            free_token(new_token);

            new_token = NULL;

            break;

        }

    }


    return new_token;

}
