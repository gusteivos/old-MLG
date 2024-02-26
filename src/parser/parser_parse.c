#include <parser.h>


AST_node_t *parser_parse(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    return parser_parse_statements(parser);

}

AST_node_t *parser_parse_statement(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    switch (parser->current_token->type)
    {

    case TOKEN_KEYWORD_T_INT8 :
    case TOKEN_KEYWORD_T_INT16:
    case TOKEN_KEYWORD_T_INT32:
    case TOKEN_KEYWORD_T_INT64:
        
        return parser_parse_variable(parser, false, TOKEN_SEMICOLON);


    case TOKEN_KEYWORD_FUNCTION: return parser_parse_function(parser);

    case TOKEN_L_BRACE:

        parser_next_token(parser);

        return parser_parse_statements(parser);


    default:

        fprintf(stderr, "Unexpected token type %d, with value %s.\n", parser->current_token->type, parser->current_token->value);


        exit(EXIT_FAILURE);

        break;

    }

    return create_AST_node(AST_NODE_NOOP);

}

AST_node_t *parser_parse_statements(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    AST_node_t *statements_node = create_AST_node(AST_NODE_COMPOUND);

    statements_node->compound = create_list();


    while (parser->current_token->type != TOKEN_R_BRACE && parser->current_token->type != TOKEN_EOF)
    {

        AST_node_t *next_statement = parser_parse_statement(parser);

        list_add(statements_node->compound, (void *)next_statement);


        parser_next_token(parser);

    }

    return statements_node;

}


/* literal number, identifier, function call, call, ( expression ), +, -, !, ~ */
AST_node_t *parser_parse_factor(parser_t *parser)
{



}


/* factor, *, /, % */
AST_node_t *parser_parse_arithmetic_term(parser_t *parser)
{

    AST_node_t *left = parser_parse_factor(parser);

    
    while (parser->current_token->type == TOKEN_ASTERISK
        || parser->current_token->type == TOKEN_SLASH
        || parser->current_token->type == TOKEN_PERCENT)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_arithmetic_term(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}

/* arithmetic term, +, - */
AST_node_t *parser_parse_arithmetic_expression(parser_t *parser)
{

    AST_node_t *left = parser_parse_arithmetic_term(parser);


    while (parser->current_token->type == TOKEN_PLUS
        || parser->current_token->type == TOKEN_MINUS)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_arithmetic_expression(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}


/* arithmetic expression, <<, >> */
AST_node_t *parser_parse_bitwise_term(parser_t *parser)
{

    AST_node_t *left = parser_parse_arithmetic_expression(parser);

    
    while (parser->current_token->type == TOKEN_L_SHIFT
        || parser->current_token->type == TOKEN_R_SHIFT)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_bitwise_term(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}


/* bitwise term, <, <=, >, >= */
AST_node_t *parser_parse_relational_term(parser_t *parser)
{

    AST_node_t *left = parser_parse_bitwise_term(parser);


    while (parser->current_token->type == TOKEN_LES_THAN
        || parser->current_token->type == TOKEN_LES_OR_EQUAL
        || parser->current_token->type == TOKEN_GRE_THAN
        || parser->current_token->type == TOKEN_GRE_OR_EQUAL)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_relational_term(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}

/* relational term, ==, != */
AST_node_t *parser_parse_relational_expression(parser_t *parser)
{

    AST_node_t *left = parser_parse_relational_term(parser);

    
    while (parser->current_token->type == TOKEN_EQUAL
        || parser->current_token->type == TOKEN_NOT_EQUAL)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_relational_expression(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}


/* relational expression, & */
AST_node_t *parser_parse_bitwise_expression_and(parser_t *parser)
{

    AST_node_t *left = parser_parse_relational_expression(parser);

    
    while (parser->current_token->type == TOKEN_AMPERSAND)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_bitwise_expression_and(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}

/* expression and, ^ */
AST_node_t *parser_parse_bitwise_expression_xor(parser_t *parser)
{

    AST_node_t *left = parser_parse_bitwise_expression_and(parser);

    
    while (parser->current_token->type == TOKEN_AMPERSAND)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_bitwise_expression_xor(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}

/* expression xor, | */
AST_node_t *parser_parse_bitwise_expression_or (parser_t *parser)
{

    AST_node_t *left = parser_parse_bitwise_expression_xor(parser);

    
    while (parser->current_token->type == TOKEN_AMPERSAND)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_bitwise_expression_or (parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}


/* expression or, && */
AST_node_t *parser_parse_logical_term(parser_t *parser)
{

    AST_node_t *left = parser_parse_bitwise_expression_or (parser);

    
    while (parser->current_token->type == TOKEN_AND)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_logical_term(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}

/* logical_term, || */
AST_node_t *parser_parse_logical_expression(parser_t *parser)
{

    AST_node_t *left = parser_parse_logical_term(parser);

    
    while (parser->current_token->type == TOKEN_AND)
    {
    
        operator_t operator = parser_token_type_to_binary_operator(parser->current_token->type);

        parser_next_token(parser);


        AST_node_t *right = parser_parse_logical_expression(parser);


        AST_node_t *binary_operation_node = create_AST_node(AST_NODE_BINARY_OPERATION);

        binary_operation_node->binary_left_factor = left;

        binary_operation_node->binary_operator = operator;

        binary_operation_node->binary_right_factor = right;


        left = binary_operation_node;

    }

    return left;

}

AST_node_t *parser_parse_expression(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    return parser_parse_logical_expression(parser);

}



AST_node_t *parser_parse_variable(parser_t *parser, bool just_declaration, token_type_t completion_token_type)
{
    
    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }


    data_type_type_t variable_type;

    variable_type = DATA_TYPE_NONE; 


    switch (parser->current_token->type)
    {

    default:

        variable_type = parser_token_type_to_data_type_type(parser->current_token->type);

        if (variable_type == DATA_TYPE_NONE)
        {

            fprintf(stderr, "Error: unsupported token type %d.\n", parser->current_token->type);        


            exit(EXIT_FAILURE);
        }        
    
        break;
    
    }

    parser_next_token(parser);


    if (parser->current_token->type != TOKEN_ID)
    {

        fprintf(stderr, "Error: a token of type TOKEN_ID was expected but we have one of type %d.\n", parser->current_token->type);


        exit(EXIT_FAILURE);

    }


    AST_node_t *node = create_AST_node(AST_NODE_VARIABLE_DEFINITION);

    if (node == NULL)
    {

        fprintf(stderr, "Error: creating node for a function.\n");


        exit(EXIT_FAILURE);

    }

    node->variable_type = variable_type;

    node->variable_name = parser->current_token->value;

    parser_next_token(parser);


    if (just_declaration == false)
    {



    }
    else
    {

        node->type = AST_NODE_VARIABLE_DECLARATION;
    
        if (parser->current_token->type != completion_token_type)
        {

            fprintf(stderr, "Error: todo %d %d\n", parser->current_token->type, completion_token_type);


            exit(EXIT_FAILURE);

        }

    }
    

    return node;

}


AST_node_t *parser_parse_function(parser_t *parser)
{

    if (parser == NULL)
    {

        fprintf(stderr, "Error: parser is NULL.\n");


        return NULL;

    }

    parser_consume_token(parser, TOKEN_KEYWORD_FUNCTION, true);


    if (parser->current_token->type != TOKEN_ID)
    {

        fprintf(stderr, "Error: a token of type TOKEN_ID was expected but we have one of type %d.\n", parser->current_token->type);


        exit(EXIT_FAILURE);

    }


    AST_node_t *node = create_AST_node(AST_NODE_FUNCTION_DEFINITION);

    if (node == NULL)
    {

        fprintf(stderr, "Error: creating node for a function.\n");


        exit(EXIT_FAILURE);

    }


    node->function_name = parser->current_token->value;


    parser_eat_token    (parser, TOKEN_L_PAREN, true);


    /* TODO: parsing arguments for the function. */

    parser_next_token(parser);


    parser_consume_token(parser, TOKEN_R_PAREN, true);

    parser_consume_token(parser, TOKEN_COLON        , true);


    switch (parser->current_token->type)
    {

    case TOKEN_KEYWORD_NONE:

        /*TODO: */

        break;

    default:

        fprintf(stderr, "Error: unsupported token type %d for return type.\n", parser->current_token->type);


        exit(EXIT_FAILURE);

        break;

    }

    parser_next_token(parser);


    switch (parser->current_token->type)
    {

    case TOKEN_SEMICOLON:

        node->type = AST_NODE_FUNCTION_DECLARATION;

        break;

    case TOKEN_L_BRACE:

        node->function_body = parser_parse_statement(parser);

        break;

    default:

        fprintf(stderr, "Error: unsupported token type %d.\n", parser->current_token->type);


        exit(EXIT_FAILURE);

        break;

    }


    return node;

}
