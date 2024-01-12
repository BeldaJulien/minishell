#include "minishell.h"

int ft_check_pipe(char *token) 
{
    return (ft_strcmp(token, "|") == 0);
}

int ft_check_heredoc(char *token) 
{
    return (ft_strcmp(token, "<<") == 0);
}

int ft_check_lpr(char *token) 
{
    return (ft_strcmp(token, "(") == 0);
}

int ft_check_rpr(char *token) 
{
    return (ft_strcmp(token, ")") == 0);
}

int ft_check_and(char *token) 
{
    return (ft_strcmp(token, "&&") == 0);
}