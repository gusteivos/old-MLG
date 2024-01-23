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
