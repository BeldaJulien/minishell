#include "minishell.h"

t_token_type ft_check_end(char *token) 
{
    if (*token == '\0') 
    {
        return END;
    }
    return 1;
}

t_token_type ft_check_command(char *token) 
{
    (void)token;
    return COMMAND_TYPE;
}

t_token_type ft_check_argument(char *token) 
{
    (void)token;
    return ARGUMENT_TYPE;
}

t_token_type ft_check_option(char *token) 
{
    (void)token;
    return OPTION_TYPE;
}

t_token_type ft_check_unknown_type(char *token) 
{
    (void)token;
    return UNKNOWN_TYPE;
}