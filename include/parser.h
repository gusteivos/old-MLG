
#ifndef PARSER_H_
#define PARSER_H_

    #include <token.h>
    #include <AST_node.h>


    typedef struct parser_s
    {

        list_t *token_list;

        int token_index;

        token_t *current_token;

    } parser_t;
    

    extern parser_t *create_parser(list_t *token_list);
    

    extern token_t *parser_next_token(parser_t *parser);

    extern token_t *parser_peek_token(parser_t *parser, int offset);

    extern bool parser_eat_token     (parser_t *parser, token_type_t type, bool can_exit);

    extern bool parser_consume_token (parser_t *parser, token_type_t type, bool can_exit);


    extern AST_node_t *parser_parse                    (parser_t *parser);
    
    extern AST_node_t *parser_parse_statement          (parser_t *parser);
    
    extern AST_node_t *parser_parse_statements         (parser_t *parser);

    extern AST_node_t *parser_parse_function_definition(parser_t *parser);


    extern void free_parser(parser_t *parser);

#endif
