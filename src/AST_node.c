#include <AST_node.h>


AST_node_t *create_AST_node(AST_node_type_t type)
{

    AST_node_t *new_node = (AST_node_t *)calloc(1, sizeof(AST_node_t));

    if (new_node == NULL)
    {

        fprintf(stderr, "Error: allocating memory for a new node.\n");


        return NULL;

    }


    new_node->type = type;

    switch (new_node->type)
    {
    
    case AST_NODE_COMPOUND:
        
        new_node->compound = create_list();

        break;

    }

    
    return new_node;

}


void free_AST_node(AST_node_t *node)
{

    if (node == NULL)
    {

        fprintf(stderr, "Error: node is NULL.\n");


        return;

    }


    /* for the future. */


    free(node);

}
