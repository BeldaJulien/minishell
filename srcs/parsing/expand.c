#include "minishell.h"

void ft_found_and_replace_usd(t_command *command, t_env *envList) 
{
    
    int i = 0;

    while (command->args[i] != NULL) 
    {
        if (command->args[i][0] == '$') 
        {
            if (command->args[i][1] != '\0') 
                command->args[i] = ft_replace_usd_to_env(envList, command->args[i]);
        }
        i++;
    }
}

char *ft_replace_usd_to_env(t_env *envList, char *usd) 
{
    
    t_env *tmp = envList;

    while (tmp) 
    {
        if (tmp->name != NULL && strcmp(usd + 1, tmp->name) == 0) 
        {
            break;
        }
        tmp = tmp->next;
    }
    if (tmp) 
    {
        free(usd);
        return strdup(tmp->value);
    } 
    else 
    {
        free(usd);
        return strdup("\0");
    }
}


void replace_env_variables_in_command(t_command *command, t_env *envList)
{
    int i = 0;
    
    while (command->args[i])
    {
        char *dollar_sign = strchr(command->args[i], '$');
        if (dollar_sign != NULL)
        {
            // Appeler votre fonction de remplacement ici
            command->args[i] = ft_replace_usd_to_env(envList, command->args[i]);
        }
        i++;
    }
}
