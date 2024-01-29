#include "minishell.h"

t_token_type ft_checkType(TokenChecker checker, char *token) 
{
    return checker(token);
}

// t_token_type ft_allocate_token_type(char *token, int tokenIndex) 
// {
//     if (ft_checkType(ft_check_pipe, token)) return PIPE;
//     if (ft_checkType(ft_check_heredoc, token)) return HEREDOC;
//     if (ft_checkType(ft_check_lpr, token)) return LPR;
//     if (ft_checkType(ft_check_rpr, token)) return RPR;
//     if (ft_checkType(ft_check_and, token)) return AND;
//     if (ft_checkType(ft_check_or, token)) return OR;
//     if (ft_checkType(ft_check_append, token)) return APPEND;
//     if (ft_checkType(ft_check_out, token)) return OUT;
//     if (ft_checkType(ft_check_in, token)) return IN;
//     if (ft_checkType(ft_check_not, token)) return NOT;
//     if (ft_checkType(ft_check_end, token)) return END;
//     if (ft_checkType(ft_check_command, token)) return COMMAND_TYPE;
//     if (ft_checkType(ft_check_argument, token)) return ARGUMENT_TYPE;
//     if (ft_checkType(ft_check_option, token)) return OPTION_TYPE;

//     return UNKNOWN_TYPE;
// }

t_token_type ft_allocate_token_type(char *token) 
{
    if (token[0] != '-') 
    {
        return COMMAND_TYPE;
    }
    else 
    {
        return ARGUMENT_TYPE;
    }
}