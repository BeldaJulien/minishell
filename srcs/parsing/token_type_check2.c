#include "minishell.h"

t_token_type ft_check_or(char *token) 
{
    return (ft_strcmp(token, "||") == 0);
}

t_token_type ft_check_append(char *token) 
{
    return (ft_strcmp(token, ">>") == 0);
}

t_token_type ft_check_out(char *token) 
{
    return (ft_strcmp(token, ">") == 0);
}

t_token_type ft_check_in(char *token) 
{
    return (ft_strcmp(token, "<") == 0);
}

t_token_type ft_check_not(char *token) 
{
    // You might want to add more conditions based on your criteria for a NOT token
    return (ft_strcmp(token, "NOT") == 0);
}
