#include "minishell.h"

int ft_is_alpha(char c) 
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        return (0);
    }
    return (1);
}

int ft_check_variable_definition(const char *arg)
{
    char *equals;
    
    equals = ft_strchr(arg, '=');
    if (equals == NULL || equals == arg || equals[1] == '\0') 
    {
        perror("Invalid variable definition. Use VARIABLE=value format.\n");
        exit(EXIT_FAILURE);
    }
    return (0);
}

int ft_check_export_args(t_command *command)
 {
    char *arg;
    int i;

    if (command->argCount > 1) 
    {
        perror("Hey, export takes only one argument!\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    arg = command->args[1];
    printf("args[0] is : %s\n", command->args[0]);
    printf("args[1] is : %s\n", command->args[1]);
    printf("arg is : %s\n", arg);
    printf("arg[0] is : %c\n", arg[0]);
    if ((!ft_is_alpha(arg[0])) || arg[0] != '_') 
    {
        perror("Export variable must start by a letter or _ \n");
        exit(EXIT_FAILURE);
    }
    i = 1;
    while (arg[i] != '\0') 
    {
        if (!ft_is_alpha(arg[i]) && arg[i] != '_') 
        {
            perror("Export variable must contain only letters, numbers, or _ \n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    ft_check_variable_definition(arg);
    return 0;
}

void ft_print_exported_vars(t_env *envList) 
{
    t_env *current;
    
    current = envList;
    while (current != NULL) 
    {
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

int ft_export(t_env **envList, t_command *cmd)
{
    t_env *current;
    t_env *newVar;

    if (ft_strcmp(cmd->name, "export") == 0 && cmd->argCount == 0)
    {
        ft_print_exported_vars(*envList);
        return (0);
    }
    ft_check_export_args(cmd);
    printf("ft_check_export_args pass successfully\n");
    ft_check_reserved_env_variables(cmd->name);

    current = *envList;
    while (current != NULL)
    {
        if (ft_strcmp(current->name, cmd->name) == 0)
        {
            free(current->value);
            current->value = ft_strdup(cmd->data);
            return (0);
        }
        current = current->next;
    }
    newVar = ft_create_node_for_envVar(cmd);
    ft_add_to_list(envList, newVar);
    return (0);
}
