
#ifndef AST_NODE_H_
#define AST_NODE_H_

    #include <list.h>
    #include <data_type.h>


    typedef enum AST_node_type_e
    {

        AST_NODE_NOOP = 0,

        AST_NODE_COMPOUND,

        AST_NODE_VARIABLE_DECLARATION,
        AST_NODE_VARIABLE_DEFINITION ,
        AST_NODE_VARIABLE_USAGE      ,
        AST_NODE_VARIABLE_ASSIGNMENT ,

        AST_NODE_FUNCTION_DECLARATION,
        AST_NODE_FUNCTION_DEFINITION ,
        AST_NODE_FUNCTION_CALL       ,

        AST_NODE_CALL,

        AST_NODE_FACTOR          ,
        AST_NODE_UNARY_OPERATION ,
        AST_NODE_BINARY_OPERATION,

    } AST_node_type_t;

    typedef enum operator_e
    {

        OPERATOR_NONE = 0,

        OPERATOR_ARITHMETIC_ADD,
        OPERATOR_ARITHMETIC_SUB,
        OPERATOR_ARITHMETIC_MUL,
        OPERATOR_ARITHMETIC_DIV,
        OPERATOR_ARITHMETIC_MOD,

        OPERATOR_BITWISE_AND    ,
        OPERATOR_BITWISE_OR     ,
        OPERATOR_BITWISE_XOR    ,
        OPERATOR_BITWISE_L_SHIFT,
        OPERATOR_BITWISE_R_SHIFT,
        OPERATOR_BITWISE_NOT    ,

        OPERATOR_LOGIC_AND,
        OPERATOR_LOGIC_OR ,
        OPERATOR_LOGIC_NOT,

        OPERATOR_RELATIONAL_LES_THAN,
        OPERATOR_RELATIONAL_LES_THAN_OR_EQUAL,
        OPERATOR_RELATIONAL_GRE_THAN,
        OPERATOR_RELATIONAL_GRE_THAN_OR_EQUAL,
        OPERATOR_RELATIONAL_EQUAL_TO,
        OPERATOR_RELATIONAL_NOT_EQUAL_TO,

    } operator_t;

    typedef struct AST_node_s
    {

        AST_node_type_t type;


        list_t *compound;


        /* TEMP: */

            char *variable_name;

            struct AST_node_s *variable_initial_expression;

            data_type_type_t   variable_type;

            /* ON VAR ASSING */

            struct AST_node_s *variable_assing_expression;

        /* TEMP: */

            char              *function_name;

            list_t            *function_args;

            data_type_type_t   function_return_type;

            /* ON FUNC DEF */

            struct AST_node_s *function_body;

        /* TEMP: */

            operator_t unary_operator;

            struct AST_node_s *unary_factor;

        /* TEMP: */

            operator_t binary_operator;

            struct AST_node_s *binary_left_factor;
 
            struct AST_node_s *binary_right_factor;

    } AST_node_t;


    extern AST_node_t *create_AST_node(AST_node_type_t type);


    extern void free_AST_node(AST_node_t *node);

#endif
