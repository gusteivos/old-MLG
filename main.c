#include <main.h>


int main(int argc, char *argv[])
{

    if (argc < 2)
    {

        usage(false, EXIT_FAILURE);

    }


    char *source_code = read_file_to_string(argv[1]);

    if (source_code == NULL)
    {

        fprintf(stderr, ".\n");


        return EXIT_FAILURE;

    }


    lexer_t *lexer = create_lexer(source_code);

    free(source_code);


    list_t *token_list = create_list();


    bool can_exit = false;

    token_t *current_token = NULL;

    lexer_skip_spaces(lexer);


    while(!can_exit)
    {

        current_token = lexer_next_token(lexer);

        if (current_token == NULL)
        {

            free_lexer(lexer);

            free_list(token_list);


            return EXIT_FAILURE;

        }


        if (current_token->type != TOKEN_NONE)
        {

            printf("token (type: %2d), (value: %s).\n", current_token->type, current_token->value);

            if (list_add(token_list, (void *)current_token) == false)
            {

                /* TODO: */

            }

        }
        else
        {

            free_token(current_token);

        }
        

        if (current_token->type == TOKEN_EOF)
        {

            can_exit = true;


            continue;

        }


        lexer_next_char(lexer);

    }


    parser_t *parser = create_parser(token_list);

    
    AST_node_t *root_node = parser_parse(parser);


    printf("root_node->compound->count == %d.\n", root_node->compound->count);


    free_lexer(lexer);

    free_list(token_list);


    return EXIT_SUCCESS;

}


void usage(bool show_help, int exit_status)
{

    printf
    (
        "\n"
        "  Usage: mlgc ./file/path.extension\n"
        "\n"
        "  Options:\n"
        "\n"
    );

if (show_help)
{

    printf
    (
        "    -h, --help            output this help information\n"
        "\n"
    );
   
}


    exit(exit_status);

}
