#include <io_utils.h>


char *read_file_to_string(const char *file_path)
{

    char *data_buffer = NULL;


    FILE *file = fopen(file_path, "r");

    if (file == NULL)
    {

        fprintf(stderr, "Error, opening file in path: %s.\n", file_path);


        goto endoffunc;

    }


    fseek(file, 0, SEEK_END);

    long file_size = ftell(file);

    fseek(file, 0, SEEK_SET);


    data_buffer = (char *)malloc((file_size + 1) * sizeof(char));

    if (data_buffer == NULL)
    {

        fprintf(stderr, "Error allocating memory for file contents from path: %s.\n", file_path);


        fclose(file);


        goto endoffunc;

    }


    size_t read_elements = fread(data_buffer, sizeof(char), (size_t)file_size, file);

    if (read_elements == 0)
    {

        fprintf(stderr, "Error, reading file from path: %s.\n", file_path);


        free(data_buffer);

        data_buffer = NULL;

        fclose(file);


        goto endoffunc;

    }


    data_buffer[read_elements] = '\0';

    fclose(file);


endoffunc:

    return data_buffer;

}


char *get_file_path_from_path(const char *file_path)
{

    if (file_path == NULL)
    {

        fprintf(stderr, "Error, file_path is NULL.\n");


        return NULL;

    }


    const char *last_slash = strrchr(file_path, '/');


#if (defined(_WIN32) || defined(_win32))
    
    const char *last_backslash = strrchr(file_path, '\\');

#else

    const char *last_backslash = NULL;

#endif


    const char *last_separator = (last_slash > last_backslash) ? last_slash : last_backslash;

    if (last_separator != NULL)
    {
    
        size_t file_path_length = strlen(last_separator + 1);

        char *file_path = (char *)malloc(file_path_length + 1);
        
        if (file_path != NULL)
        {
        
            strcpy(file_path, last_separator + 1);
        
        
            return file_path;
        
        }
    
    }


    return NULL;

}
