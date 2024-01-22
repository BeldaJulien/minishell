#include "minishell.h"

t_token_type ft_check_end(char *token) 
{
    return (ft_strcmp(token, "END") == 0);
}

t_token_type ft_check_command(char *token) 
{
    // You might want to add more conditions based on your criteria for a COMMAND_TYPE token
    return (ft_strcmp(token, "COMMAND_TYPE") == 0);
}

t_token_type ft_check_argument(char *token) 
{
    // You might want to add more conditions based on your criteria for an ARGUMENT_TYPE token
    return (ft_strcmp(token, "ARGUMENT_TYPE") == 0);
}

t_token_type ft_check_option(char *token) 
{
    // You might want to add more conditions based on your criteria for an OPTION_TYPE token
    return (ft_strcmp(token, "OPTION_TYPE") == 0);
}

t_token_type ft_check_unknown_type(char *token) 
{
    // You might want to add more conditions based on your criteria for an UNKNOWN_TYPE token
    return (ft_strcmp(token, "UNKNOWN_TYPE") == 0);
}