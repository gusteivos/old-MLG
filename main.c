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


    bool can_exit = false;

    token_t *curent_token = NULL;

    lexer_skip_spaces(lexer);


    while(!can_exit)
    {

        curent_token = lexer_next_token(lexer);

        if (curent_token == NULL)
        {

            fprintf(stderr, "TODO: .\n");


            return EXIT_FAILURE;

        }


        if (curent_token->type != TOKEN_NONE)
        {

            printf("token (type: %2d), (value: %s).\n", curent_token->type, curent_token->value);

        }


        if (curent_token->type == TOKEN_EOF)
        {

            can_exit = true;


            continue;

        }


        lexer_next_char(lexer);

    }



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
