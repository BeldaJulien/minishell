#include "minishell.h"

void ft_add_to_list(t_env **envlist, t_env *new_node) 
{
    t_env *current; 

    if (!envlist || !new_node)
        return;

    if (!*envlist) 
    {
        *envlist = new_node;
        return;
    }

    current = *envlist;
    while (current->next != NULL) 
    {
        current = current->next; 
    }
    current->next = new_node;
}

int	ft_add_envVar_to_list(t_env **envlist, t_env *new_node, t_command *command)
{
	new_node = NULL;
	new_node = ft_create_node_for_envVar(command);
	if (!new_node)
		return (0);
	if (!ft_is_in_list(new_node->name, envlist))
		ft_add_to_list(envlist, new_node);
	else
		ft_replace_in_list(new_node, envlist);
	return (1);
}

void ft_initialize_list(t_commandList *commandList, t_command *newCommand) 
{
    if (commandList == NULL || newCommand == NULL) 
    {
        fprintf(stderr, "Error: Invalid commandList or newCommand.\n");
        exit(EXIT_FAILURE);
    }

    if (commandList->head != NULL || commandList->tail != NULL) 
    {
        fprintf(stderr, "Error: Attempting to initialize a non-empty list\n");
        exit(EXIT_FAILURE);
    }

    commandList->head = newCommand;
    commandList->tail = commandList->head;
    commandList->length = 1;
}

void ft_append_to_list(t_commandList *commandList, t_command *newCommand) 
{
    if (commandList == NULL || newCommand == NULL) 
    {
        fprintf(stderr, "Error: Invalid commandList or newCommand.\n");
        exit(EXIT_FAILURE);
    }

    if (commandList->tail == NULL) 
    {
        fprintf(stderr, "Error: Attempting to append to an empty list\n");
        exit(EXIT_FAILURE);
    }

    if (commandList->head == NULL) 
    {
        ft_initialize_list(commandList, newCommand);
    } 
    else 
    {
        if (commandList->tail->next != NULL) 
        {
            fprintf(stderr, "Error: Inconsistent list structure\n");
            exit(EXIT_FAILURE);
        }

        commandList->tail->next = newCommand;
        commandList->tail = commandList->tail->next;
        commandList->tail->next = NULL;
        commandList->length++;
    }
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