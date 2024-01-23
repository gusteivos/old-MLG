#include <utils.h>


char alpha_others[] = "_";

char digit_others[] = ".";


bool is_alpha(char c)
{

    return isalpha(c) > 0;

}

bool is_digit(char c)
{

    return isdigit(c) > 0;

}

bool is_alpha_or_others(char c, char *others)
{

    return isalpha(c) || (c != '\0' && strchr(others, c) != NULL);

}

bool is_digit_or_others(char c, char *others)
{

    return isdigit(c) || (c != '\0' && strchr(others, c) != NULL);

}


void *safe_realloc(void *ptr, size_t new_size)
{
    if (ptr == NULL)
    {
    
        return malloc(new_size);
    
    }


    void *new_ptr = realloc(ptr, new_size);

    if (new_ptr == NULL)
    {

        new_ptr = malloc(new_size);
    
        if (new_ptr == NULL)
        {
        
            /* fprintf(stderr, "Unable to allocate memory in any way.\n"); */
        

            return NULL;
        
        }
        
        memcpy(new_ptr, ptr, new_size);
        

        free(ptr);
    
    }


    return new_ptr;

}
