#include <list.h>


list_t *create_list         ()
{

    return create_list_capacity(LIST_DEFAULT_CAPACITY);

}

list_t *create_list_capacity(int capacity)
{

    if (capacity < 0)
    {

        fprintf(stderr, "Error: invalid capacity for list.\n");


        return NULL;

    }


    list_t *new_list = (list_t *)malloc(sizeof(list_t));

    if (new_list == NULL)
    {

        fprintf(stderr, "Error: allocating memory for a new list.\n");


        return NULL;

    }


    new_list->capacity = capacity;


    if (new_list->capacity > 0)
    {

        new_list->items = (void **)calloc(new_list->capacity, sizeof(void *));

        if (new_list->items == NULL)
        {

            fprintf(stderr, "Error: allocating memory for items in the new list.\n");


            free(new_list);


            return NULL;

        }

    }


    new_list->count = 0;


    return new_list;

}


bool list_realloc(list_t *list, int new_capacity)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return false;

    }


    list->items = (void **)safe_realloc(list->items, new_capacity * sizeof(void *));


    memset(list->items + list->capacity, 0, (new_capacity - list->capacity) * sizeof(void *));


    list->capacity = new_capacity;


    return true;

}


void free_list(list_t *list)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return;

    }


    if (list->items != NULL)
    {

        free(list->items);

    }


    free(list);

}
