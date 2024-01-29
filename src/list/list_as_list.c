#include <list.h>


bool list_add   (list_t *list, void *value)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return false;

    }


    if (list->count >= list->capacity)
    {

        int new_capacity = list->capacity + (list->count - list->capacity) + 1;

        list_realloc(list, new_capacity);

    }


    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] == NULL)
        {

            list->items[q] = value;

            list->count++;


            break;

        }

    }


    return true;

}

bool list_remove(list_t *list, void *value)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return false;

    }


    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] == value)
        {

            list->items[q] = NULL;

            list->count--;


            break;

        }

    }


    return true;

}

void *list_get  (list_t *list, void *value)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return NULL;

    }


    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] == value)
        {

            return value;

        }

    }


    return NULL;

}

void *list_set  (list_t *list, void *value, void *new_value)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return NULL;

    }


    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] == value)
        {

            list->items[q] = new_value;


            return value;

        }

    }


    return NULL;

}
