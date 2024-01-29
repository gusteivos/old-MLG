
#ifndef LIST_H_
#define LIST_H_

    #include <utils.h>


    #ifndef LIST_DEFAULT_CAPACITY
    #define LIST_DEFAULT_CAPACITY 8
    #endif


    typedef struct list_s
    {

        int capacity;

        int count   ;

        void **items;

    } list_t;


    extern list_t *create_list         (void);

    extern list_t *create_list_capacity(int capacity);


    extern bool list_realloc(list_t *list, int new_capacity);


    extern bool list_add   (list_t *list, void *value);

    extern bool list_remove(list_t *list, void *value);

    extern void *list_get  (list_t *list, void *value);

    extern void *list_set  (list_t *list, void *value, void *new_value);


    extern bool list_remove_by_index(list_t *list, int index);

    extern void *list_get_by_index  (list_t *list, int index);

    extern void *list_set_by_index  (list_t *list, int index, void *new_value);


    extern void free_list(list_t *list);

#endif
