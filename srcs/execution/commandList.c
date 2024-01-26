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

void ft_execute_command_list(t_commandList *commandList, t_env *envList, char **envp) 
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
            ft_execute_piped_commands(commandList, current_command, num_commands, envList, envp);
        } 
        else 
        {
            // Execute single command
            ft_execute_single_command(current_command, commandList, envList, envp);
        }

        current_command = current_command->next;
    }
}

void ft_destroy_commandList(t_commandList *commandList) 
{
    if (commandList == NULL) {
        fprintf(stderr, "Error: NULL pointer in ft_destroy_commandList\n");
        return;
    }

    t_command *currentCommand = commandList->head;
    t_command *nextCommand;

    while (currentCommand != NULL) {
        nextCommand = currentCommand->next;

        // Libérer la mémoire associée à la commande
        free(currentCommand->name);

        // Supprimer la mémoire associée aux arguments de la commande (si nécessaire)
        int i = 0;
        while (currentCommand->args[i] != NULL) {
            free(currentCommand->args[i]);
            i++;
        }
        free(currentCommand->args);

        free(currentCommand);

        currentCommand = nextCommand;
    }

    // Réinitialiser la structure de la liste des commandes
    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
}



void ft_print_commandList(t_commandList *commandList) 
{
    if (commandList == NULL || commandList->head == NULL) 
    {
        fprintf(stderr, "Command list is empty or NULL.\n");
        return;
    }
    
    int i;
    t_command *current;
    
    current = commandList->head;

    printf("Command List:\n");

    while (current != NULL) 
    {
        printf("Command: %s\n", current->name);

        // Print arguments
        i = 0;
        while (i < current->argCount) 
        {
            printf("Argument %d: %s\n", i, current->args[i]);
            i++;
        }
        current = current->next;
    }
}