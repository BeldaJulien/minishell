#include "minishell.h"

void ft_initialize_commandList(t_commandList *commandList) 
{
    if (commandList == NULL) 
    {
        fprintf(stderr, "Error: NULL pointer in ft_init_commandList\n");
        exit(EXIT_FAILURE);
    }

    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
}

void ft_execute_command_list(t_commandList *commandList, t_global *global_data, char **envp) 
{
    int num_commands;
    t_command *current_command;
    
    current_command = commandList->head;

    while (current_command != NULL) 
    {
        if (current_command->tokenType == PIPE) 
        {
            // Execute commands with pipes
            num_commands = ft_count_piped_commands(current_command);
            ft_execute_piped_commands(current_command, num_commands, global_data, envp);
        } 
        else 
        {
            // Execute single command
            ft_execute_single_command(current_command, global_data, envp);
        }

        current_command = current_command->next;
    }
}
