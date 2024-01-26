#include "minishell.h"

t_token_type ft_check_or(char *token) 
{
    if (ft_strcmp(token, "||") == 0)
        return OR;
    return 1;
}

t_token_type ft_check_append(char *token) 
{
    if (ft_strcmp(token, ">>") == 0)
        return APPEND;
    return 1;
}

t_token_type ft_check_out(char *token) 
{
    if (ft_strcmp(token, ">") == 0)
        return OUT;
    return 1;
}

t_token_type ft_check_in(char *token) 
{
    if (ft_strcmp(token, "<") == 0)
        return IN;
    return 1;
}

t_token_type ft_check_not(char *token) 
{
    (void)token;
    return NOT;
    return 1;
}
