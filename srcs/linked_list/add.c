#include "minishell.h"

void ft_add_to_list(t_env **envList, t_env *new_node)
{
    t_env *current;

    if (envList == NULL || new_node == NULL)
    {
        return;
    }

    if (*envList == NULL)
    {
        *envList = new_node;
    }
    else
    {
        current = *envList;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
        new_node->prev = current;
    }
}

// int	ft_add_envVar_to_list(t_env **envlist, t_env *new_node, t_command *command)
// {
// 	new_node = NULL;
// 	new_node = ft_create_node_for_envVar(command);
// 	if (!new_node)
// 		return (0);
// 	if (!ft_is_in_list(new_node->name, envlist))
// 		ft_add_to_list(envlist, new_node);
// 	else
// 		ft_replace_in_list(new_node, envlist);
// 	return (1);
// }

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

void ft_append_to_commandList(t_commandList *commandList, t_command *newNode) 
{
    if (commandList == NULL || newNode == NULL) 
    {
        perror("Error in ft_append_to_list: Invalid commandList or newCommand.\n");
        exit(EXIT_FAILURE);
    }

    newNode->next = NULL;

     if (commandList->head == NULL) 
     {
        commandList->head = newNode;
        commandList->tail = newNode;
    } else 
    {
        commandList->tail = newNode;
        commandList->tail->next = NULL;
    }
    commandList->length++;

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
