#include "minishell.h"

t_token_type ft_check_pipe(char *token) 
{
    if (ft_strcmp(token, "||") == 0)
        return PIPE;
    return 1;
}

t_token_type ft_check_heredoc(char *token) 
{
    if (ft_strcmp(token, "<<") == 0)
        return HEREDOC;
    return 1;
}

t_token_type ft_check_lpr(char *token) 
{
    if (ft_strcmp(token, "(") == 0)
        return LPR;
    return 1;
}

t_token_type ft_check_rpr(char *token) 
{
    if (ft_strcmp(token, ")") == 0)
        return RPR;
    return 1;
}

t_token_type ft_check_and(char *token) 
{
    if (ft_strcmp(token, "&&") == 0)
        return AND;
    return 1;
}