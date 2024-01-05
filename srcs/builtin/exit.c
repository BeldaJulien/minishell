#include "minishell.h"

int ft_search_exit_arg_in_envList(t_command *command, t_env *envList) 
{
    int g_exit_code = 0;
    t_env *current_node = envList;
    
    while (current_node != NULL) 
	{
        if (ft_strcmp(current_node->name, *command->args) == 0) 
		{
            if (!(ft_check_exit_arg_value(current_node->value))) 
			{
                perror("failed in ft_check_exit_arg_value");
                exit(EXIT_FAILURE);
            }
            g_exit_code = ft_atoi(current_node->value);
            return g_exit_code;
        }
        current_node = current_node->next;
    }
    perror("Sorry but exit argument not found in envList\n");
    exit(EXIT_FAILURE);
}

int ft_check_exit_arg_value(char *value) 
{
    int num;
	
	num = ft_atoi(value);
    if (num < 0 || num > 255) {
        perror("Exit arg number wrong. Must be between 0 to 255\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int ft_exit(t_command *command, t_env *envList) 
{
    int g_exit_code;
	
	g_exit_code = 0;
    if (command->argCount == 0) 
	{
        exit(EXIT_SUCCESS);
    } else if (command->argCount == 1) 
	{
        g_exit_code = ft_search_exit_arg_in_envList(command, envList);
        exit(g_exit_code);
    } else {
        perror("Exit failed. Take your mass gainer shaker\n");
        exit(EXIT_FAILURE);
    }
}
