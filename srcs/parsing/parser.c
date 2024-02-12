/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienbelda <julienbelda@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:44:27 by bat               #+#    #+#             */
/*   Updated: 2024/01/10 15:37:36 by julienbelda      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type ft_check_and_allocate_token_type(char *token, int tokenIndex) 
{
    if (tokenIndex == 0 && token[0] != '-') 
    {
        return COMMAND_TYPE;
    }
    else 
    {
        return ARGUMENT_TYPE;
    }
}

void process_command(t_commandList *commandList, char *token, int tokenIndex) 
{
    t_command *command = ft_create_node_for_command();
    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    command->name = ft_strdup(token);
    command->tokenType = ft_check_and_allocate_token_type(token, tokenIndex);
    command->args = (char **)malloc(sizeof(char *) * 2);
    if (command->args == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    command->args[0] = ft_strdup(token);
    command->args[1] = NULL;

    if (commandList->head == NULL) 
    {
        commandList->head = command;
        commandList->tail = commandList->head;
    } 
    else 
    {
        commandList->tail->next = command;
        commandList->tail = commandList->tail->next;
    }
    commandList->length++;
}

void process_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) 
{
    char **newArgs;
    int i;

    if (command == NULL || token == NULL) 
    {
        fprintf(stderr, "An error occurred: not enough arguments\n");
        return;
    }

    // Allouer de la mémoire pour le nouvel argument
    newArgs = (char **)malloc(sizeof(char *) * (argIndex + 2));
    if (newArgs == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    // Copier les anciens arguments dans le nouveau tableau avec une boucle while
    i = 0;
    while (i < argIndex) 
    {
        newArgs[i] = command->args[i];
        i++;
    }

    // Ajouter le nouvel argument
    newArgs[argIndex] = ft_strdup(token);
    newArgs[argIndex + 1] = NULL; // Marquer la fin du tableau d'arguments

    // Stocker les arguments mis à jour dans la structure t_command
    command->args = newArgs;
    command->argCount++;
}

int ft_split_arg(t_commandList *commandList, char *input) {
    char *token;
    int argIndex = 0;
    token = ft_strtok(input, " ");

    if (token == NULL) {
        fprintf(stderr, "An error occurred: Empty command\n");
        return 0;
    }

    // Traitement du premier token comme une commande
    process_command(commandList, token, 0);
    argIndex++;

    while ((token = ft_strtok(NULL, " ")) != NULL) {
        // Si la commande est cd, traitez le premier argument différemment
        if (argIndex == 1 && ft_strcmp(commandList->tail->name, "cd") == 0) {
            process_cd_argument(commandList->tail, token);
            break;
        }

        // Utilisez la nouvelle fonction pour extraire les arguments entre quotes
        if (process_quoted_argument(commandList, commandList->tail, token, argIndex)) {
            argIndex++;
            continue;
        }

        printf("Processing argument %d: %s\n", argIndex, token);
        process_argument(commandList, commandList->tail, token, argIndex);
        argIndex++;
    }

    // Ajoutez une chaîne NULL à la fin du tableau d'arguments
    process_argument(commandList, commandList->tail, NULL, argIndex);

    return commandList->length;
}



void process_cd_argument(t_command *command, char *arg) 
{
    // Assurez-vous que la structure t_command est correctement initialisée avec les arguments
    command->args = malloc(2 * sizeof(char *));
    command->args[0] = strdup(arg);
    command->args[1] = NULL;
}


int ft_launch_parsing(t_commandList *commandList, char *input, t_env *envList, char **envp)
{
    t_command *command;
    ft_initialize_commandList(commandList);

    if (ft_split_arg(commandList, input) > 0) 
    {
        replace_env_variables_in_command(commandList->head, envList);
        
        if (commandList != NULL && commandList->head != NULL) 
        {
            ft_print_list(commandList, ft_print_command);

            command = commandList->head;

            if (ft_is_builtin(command)) 
            {
                printf("Built-in found. Launch execute builtin of command : %s\n", command->name);
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
            fprintf(stderr, "Error: commandList or its head is NULL\n");
        }
        return 1;
    } 
    else 
    {
        perror("Parsing failed");
        ft_destroy_command(commandList);
        return 0;
    }
}

/* int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    if (token == NULL) {
        fprintf(stderr, "Error: Empty command\n");
        return 0;
    }

    // Traitement du premier token comme une commande
    t_command *command = ft_create_node_for_command();
    if (command == NULL) {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    command->name = ft_custom_strdup(token);
    command->tokenType = COMMAND_TYPE;

    if (commandList->head == NULL) {
        // Première commande dans la liste
        commandList->head = command;
        commandList->tail = commandList->head;
    } else {
        // Ajouter la commande à la fin de la liste
        commandList->tail->next = command;
        commandList->tail = commandList->tail->next;
    }

    commandList->length++;

    // Traitement des tokens suivants comme des arguments
    int argIndex = 0;
    while ((token = ft_strtok(NULL, " ")) != NULL) {
        t_command *newArg = ft_create_node_for_command();
        if (newArg == NULL) {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        newArg->name = ft_custom_strdup(token);
        newArg->tokenType = ARGUMENT_TYPE;

        // Ajouter l'argument à la fin de la liste
        commandList->tail->next = newArg;
        commandList->tail = commandList->tail->next;

        commandList->length++;

        // Stocker l'argument dans le champ args de la commande
        if (argIndex == 0) {
            command->args = malloc(sizeof(char *) * 2); // +1 pour le dernier NULL
        } else {
            command->args = realloc(command->args, sizeof(char *) * (argIndex + 2));
        }

        if (command->args == NULL) {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }

        command->args[argIndex] = newArg->name;
        command->args[argIndex + 1] = NULL;

        argIndex++;
    }

    return commandList->length;
} */