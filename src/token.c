#include <token.h>


token_mapping_t token_keyword_mappings[] =
{

    {"none", NULL, TOKEN_KEYWORD_NONE},

    {"int8" , "byte" , TOKEN_KEYWORD_T_INT8 },
    {"int16", "short", TOKEN_KEYWORD_T_INT16},
    {"int32", "int"  , TOKEN_KEYWORD_T_INT32},
    {"int64", "long" , TOKEN_KEYWORD_T_INT64},

    {"func", "function", TOKEN_KEYWORD_FUNCTION},

    {"return", "ret", TOKEN_KEYWORD_RETURN},
    {"if"    , NULL , TOKEN_KEYWORD_IF    },
    {"else"  , "el" , TOKEN_KEYWORD_ELSE  },
    {"loop"  , NULL , TOKEN_KEYWORD_LOOP  },
    {"while" , NULL , TOKEN_KEYWORD_WHILE },
    {"for"   , NULL , TOKEN_KEYWORD_FOR   },
    {"break" , NULL , TOKEN_KEYWORD_BREAK },
   
    {NULL, NULL, TOKEN_EOF}

};


token_t *create_token(token_type_t type, char *value)
{

    token_t *new_token = (token_t *)malloc(sizeof(token_t));

    if (new_token == NULL)
    {

        fprintf(stderr, "Error: allocating memory for a new token.\n");


        return NULL;

    }


    new_token->type = type;


    new_token->value = (value != NULL) ? strdup(value) : NULL;


    return new_token;

}


bool set_token(token_t *token, token_type_t type, char *value)
{

    if (token == NULL)
    {

        fprintf(stderr, "Error: token is null.\n");


        return false;

    }


    token->type = type;


    if (token->value != NULL)
    {

        free(token->value);

    }

    token->value = (value != NULL) ? strdup(value) : NULL;


    return true;

}


void free_token(token_t *token)
{

    if (token == NULL)
    {

        fprintf(stderr, "Error: token is null.\n");


        return;

    }


    if (token->value != NULL)
    {

        free(token->value);

    }


    free(token);

}


bool token_to_mapping(token_t *token, token_mapping_t *mappings, bool free_token_value)
{

    if (token == NULL || mappings == NULL)
    {

        fprintf(stderr, "Error: token or mappings are null.\n");


        return false;

    }


    int index = 0;

    token_mapping_t current = mappings[index];

    while ((current.value0 != NULL || current.value1 != NULL) && current.type != TOKEN_EOF)
    {

        if ((current.value0 != NULL && strcmp(token->value, current.value0) == 0) || (current.value1 != NULL &&  strcmp(token->value, current.value1) == 0))
        {

            if (free_token_value)
            {

                free(token->value);

                token->value = NULL;

            }


            token->type = current.type;


            break;

        }

       current = mappings[++index];

    }


    return true;

}

bool token_id_to_keyword_mapping(token_t *token)
{

    if (token == NULL)
    {

        fprintf(stderr, "Error: token is NULL.\n");


        return false;

    }

    if (token->type != TOKEN_ID)
    {

        fprintf(stderr, "Error: token not is of type TOKEN_ID.\n");


        return NULL;

    }


    return token_to_mapping(token, token_keyword_mappings, true);

}
