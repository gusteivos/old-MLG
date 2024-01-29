#include <list.h>


bool list_remove_by_index(list_t *list, int index)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return false;

    }

    if (index < 0 || index >= list->count)
    {

        fprintf(stderr, "Error: invalid list index: %d.\n", index);


        return false;

    }


    int count_index = -1;

    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] != NULL)
        {

            count_index++;


            if (count_index == index)
            {

                list->items[q] = NULL;


                return true;

            }

        }

    }


    return false;

}

void *list_get_by_index  (list_t *list, int index)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return NULL;

    }

    if (index < 0 || index >= list->count)
    {

        fprintf(stderr, "Error: invalid list index: %d.\n", index);


        return false;

    }


    int count_index = -1;

    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] != NULL)
        {

            count_index++;


            if (count_index == index)
            {

                return list->items[q];

            }

        }

    }


    return NULL;

}

void *list_set_by_index  (list_t *list, int index, void *new_value)
{

    if (list == NULL)
    {

        fprintf(stderr, "Error: list is NULL.\n");


        return NULL;

    }

    if (index < 0 || index >= list->count)
    {

        fprintf(stderr, "Error: invalid list index: %d.\n", index);


        return false;

    }


    int count_index = -1;

    for (int q = 0; q < list->capacity; q++)
    {

        if (list->items[q] != NULL)
        {

            count_index++;


            if (count_index == index)
            {

                void *old_value = list->items[q];

                list->items[q] = new_value;


                return old_value;

            }

        }

    }


    return NULL;

}
