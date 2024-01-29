#include "minishell.h"

int ft_execute_single_command(t_command *command, t_commandList *commandList, t_env *envList, char **envp) 
{
    if (command) 
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
            ft_execute_external_command(command, commandList, envp);
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
    
    full_path = ft_build_full_path(/*command->name, */commandList);

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

void ft_printCommand(t_command *command) {
    if (command != NULL) {
        printf("Command Name: %s\n", command->name);
        printf("Command Data: %p\n", command->data);
        printf("Command Arguments:\n");
        for (int i = 0; i < command->argCount; ++i) {
            printf("  Argument %d: %s\n", i, command->args[i]);
        }
        printf("Argument Count: %d\n", command->argCount);
        printf("Redirect File: %s\n", command->redirectFile);
        printf("Pipe File Descriptors: %d, %d\n", command->fd[0], command->fd[1]);
        printf("Next Command: %p\n", (void *)command->next);
        printf("Previous Command: %p\n", (void *)command->prev);
        printf("Token Type: %d\n", command->tokenType);
        printf("Quote Type: %d\n", command->quoteType);
    } else {
        printf("Command is NULL\n");
    }
}
