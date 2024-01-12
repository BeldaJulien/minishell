#include "minishell.h"

t_token_type ft_check_and_allocate_token_type(char *token, int tokenIndex) 
{
    if (tokenIndex == 0 && token[0] != '-') 
    {
        return COMMAND_TYPE;
    }
    else 
    {
        return ARGUMENT_TYPE;
    }
}

void ft_check_char_for_quote_type(char current_char, t_quote_type *quote_type) 
{
    if (*quote_type == NORMAL) 
    {
        if (current_char == '\'') 
        {
            *quote_type = SINGLE_QUOTE;
        } else if (current_char == '"') 
        {
            *quote_type = DOUBLE_QUOTE;
        }
    } else if (*quote_type == SINGLE_QUOTE) 
    {
        if (current_char == '\'') 
        {
            *quote_type = NORMAL;
        }
    } else if (*quote_type == DOUBLE_QUOTE) 
    {
        if (current_char == '"') 
        {
            *quote_type = NORMAL;
        } else if (current_char == '\\') {
            *quote_type = ESCAPED;
        }
    } else if (*quote_type == ESCAPED) {
        *quote_type = DOUBLE_QUOTE;
    }
    // Ici, vous pouvez traiter le caractère en fonction de son contexte
    // printf("Current char: %c, Quote type: %d\n", current_char, *quote_type);
}

t_quote_type ft_check_and_allocate_quote_type(char *token) 
{
    t_quote_type quote_type;
    int i;
    int tokenSize;
    char current_char;

    i = 0;
    tokenSize = ft_strlen(token);
    current_char = token[i];
    quote_type = NORMAL;

    while (i < tokenSize)
    {   
        ft_check_char_for_quote_type(current_char, &quote_type);
        i++;
    }
    return quote_type;
}
