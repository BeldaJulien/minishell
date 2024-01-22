#include "minishell.h"

int ft_execute_single_command(t_command *command, t_env *envList, char **envp) 
{
    if (command->tokenType == COMMAND_TYPE) 
    {
        if (ft_is_builtin(command)) 
        {
            printf("Built-in found. Launch execute builtin of command: %s\n", command->name);
            ft_execute_builtin(command, envList);
        } 
        else if (command->name[0] == '.' || command->name[0] == '/') 
        {
            printf("Relative or absolute path detected. Command: %s\n", command->name);
            ft_execute_command_with_path(command);
        } 
        else 
        {
            printf("External command detected. Command: %s\n", command->name);
            ft_execute_external_command(command, envList, envp);
        }
    }
    else 
    {
        // Gérer d'autres types de commandes si nécessaire
    }
    return  (0);
}

void ft_execute_external_command(t_command *command, t_commandList *commandList, char **envp) 
{
    char *full_path;
    pid_t pid;
    
    full_path = ft_build_full_path(command->name, commandList);

    if (full_path != NULL) 
    {
        pid = fork();

        if (pid == 0) 
        {
            ft_execute_child_process(full_path, command->args, envp);
        } else if (pid == -1) 
        {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        } else {
            ft_wait_for_child_process(pid);
            free(full_path);
        }
    } else {
        fprintf(stderr, "Command not found in PATH: %s\n", command->name);
    }
}
