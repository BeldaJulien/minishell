#include "minishell.h"

int	ft_is_white_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\r'
        || c == '\n' || c == '\v' || c == '\f')
        return (1);
    return (0);
}

t_Bool ft_check_only_spaces(const char *str) 
{
    if (str == NULL) 
        return FALSE;
    int i = 0;
    while (str[i] != '\0') 
    {
        if (str[i] != ' ') 
            return FALSE;
        i++;
    }
    return TRUE;
}
