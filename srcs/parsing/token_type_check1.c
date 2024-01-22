#include "minishell.h"

t_token_type ft_check_pipe(char *token) 
{
    return (ft_strcmp(token, "|") == 0);
}

t_token_type ft_check_heredoc(char *token) 
{
    return (ft_strcmp(token, "<<") == 0);
}

t_token_type ft_check_lpr(char *token) 
{
    return (ft_strcmp(token, "(") == 0);
}

t_token_type ft_check_rpr(char *token) 
{
    return (ft_strcmp(token, ")") == 0);
}

t_token_type ft_check_and(char *token) 
{
    return (ft_strcmp(token, "&&") == 0);
}