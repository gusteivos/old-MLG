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

    case TOKEN_KEYWORD_FUNC: return parser_parse_function_definition(parser);
    
    case TOKEN_L_BRACE:
    
        parser_next_token(parser);

        return parser_parse_statements(parser);
    

    default:

        fprintf(stderr, "Unexpected token type %d, with value %s.\n", parser->current_token->type, parser->current_token->value);

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

AST_node_t *parser_parse_function_definition(parser_t *parser)
{

    if (parser == NULL)
    {
 
        fprintf(stderr, "Error: parser is NULL.\n");
 
 
        return NULL;
 
    }

 
    parser_consume_token(parser, TOKEN_KEYWORD_FUNC, true);


    if (parser->current_token->type != TOKEN_ID)
    {
        
        fprintf(stderr, "Error: a token of type TOKEN_ID was expected but we have one of type %d.\n", parser->current_token->type);


        exit(EXIT_FAILURE); 

    }


    AST_node_t *node = create_AST_node(AST_NODE_FUNCTION_DEFINITION);

    
    node->function_definition_name = parser->current_token->value;


    parser_eat_token(parser, TOKEN_L_PARENTHESIS, true);

    parser_next_token(parser);


    /* TODO: parsing arguments for the function. */


    parser_consume_token(parser, TOKEN_R_PARENTHESIS, true);


    parser_consume_token(parser, TOKEN_COLON, true);


    token_t *peeked_token = parser_peek_token(parser, 1);

    /* TEMP: */
        
        if (!peeked_token->type == TOKEN_KEYWORD_NONE)
        {

            exit(EXIT_FAILURE);

        }


    parser_next_token(parser);


    /* TEMP: */
        
        if (!peeked_token->type == TOKEN_L_BRACE)
        {

            exit(EXIT_FAILURE);

        }
    

        node->function_definition_body = parser_parse_statement(parser);


    return node;

}
