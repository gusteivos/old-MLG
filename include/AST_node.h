
#ifndef AST_NODE_H_
#define AST_NODE_H_

    #include <list.h>


    typedef enum AST_node_type_e
    {

        AST_NODE_NOOP = 0,

        AST_NODE_COMPOUND,

        AST_NODE_FUNCTION_DEFINITION,

    } AST_node_type_t;

    typedef struct AST_node_s
    {

        AST_node_type_t type;


        list_t *compound;


        /* TEMP ? */

            struct AST_node_s* function_definition_body;

            char* function_definition_name;

            /* TODO: return type*/

    } AST_node_t;


    extern AST_node_t *create_AST_node(AST_node_type_t type);


    extern void free_AST_node(AST_node_t *node);

#endif
