#include "minishell.h"

void ft_appendToList(t_commandList *commandList, t_command *newCommand) 
{
    if (commandList->tail == NULL) 
    {
        fprintf(stderr, "Error: Attempting to append to an empty list\n");
        exit(EXIT_FAILURE);
    }

    commandList->tail->next = newCommand;
    newCommand->next = NULL;
}

void ft_appendToListArg(t_command *command, char *arg) 
{
    // Si nécessaire, augmentez la taille de la liste d'arguments
    char **newArgs = realloc(command->args, (command->argCount + 1) * sizeof(char *));
    if (newArgs == NULL) 
    {
        perror("CHAOS, error reallocating memory");
        exit(EXIT_FAILURE);
    }

    // Allouez de la mémoire pour la nouvelle chaîne d'argument
    newArgs[command->argCount] = ft_custom_strdup(arg);
    if (newArgs[command->argCount] == NULL) 
    {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Mettez à jour la liste d'arguments dans la structure de commande
    command->args = newArgs;
    command->argCount++;
}


void ft_print_list(t_commandList *head, void (*printFunction)(void *data)) 
{
    if (head == NULL || head->head == NULL) 
        return;
    t_command *current = head->head;
    while (current != NULL) 
    {
        printFunction(current);
        current = current->next;
    }
}

void ft_print_command(void *data) 
{
    t_command *command = (t_command *)data;
    if (command != NULL) 
        printf("Command: %s\n", command->name);
}