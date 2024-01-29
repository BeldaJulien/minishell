#include "minishell.h"

void ft_process_the_first_token_as_a_command(t_commandList *commandList, char *token) 
{
    t_command *command;
    
    command = (t_command *)malloc(sizeof(t_command));

    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    ft_init_new_node(commandList, command, token);

    ft_append_to_commandList(commandList, command);

    printf("Printing commandList at the end of ft_process_the_first_token_as_a_command:\n");
    ft_print_commandList(commandList);
}

void ft_process_token_as_an_argument(t_commandList *commandList, t_command *command, char *token, int tokenIndex) 
{
    int i;
    char **newArgs;

    printf("in ft_process_token_as_an_argument the token name is : '%s'\n", token);
    printf("in ft_process_token_as_an_argument the token index is : '%d'\n", tokenIndex);
    printf("ft_printCommand return :\n");
    ft_printCommand(command);

    if (command == NULL || token == NULL) 
    {
        perror("An error occurred in ft_process_token_as_an_argumentt: wrong input to process\n");
        return;
    }

    newArgs = (char **)malloc(sizeof(char *) * (tokenIndex + 2));
    if (newArgs == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    // Copier les anciens arguments dans le nouveau tableau avec une boucle while
    i = 0;
    while (i < tokenIndex) 
    {
        newArgs[i] = command->args[i];
        i++;
    }

    // Ajouter le nouvel argument
    newArgs[tokenIndex] = ft_strdup(token);
    newArgs[tokenIndex + 1] = NULL; // Marquer la fin du tableau d'arguments

    // Stocker les arguments mis à jour dans la structure t_command
    command->args = newArgs;
    command->argCount++;
        // Ajoutez une chaîne NULL à la fin du tableau d'arguments

}


int ft_split_input_in_token_to_commandList(t_commandList *commandList, char *input) 
{
    char *token;
    int tokenIndex;
    
    tokenIndex = 0;
    token = ft_strtok(input, " ");

    if (token == NULL) 
    {
        perror("An error has occurred during input tokenization: Empty command\n");
        return 1;
    }
    printf("Processing first command\n");

    ft_process_the_first_token_as_a_command(commandList, token);

    tokenIndex++;
    while ((token = ft_strtok(NULL, " ")) != NULL) 
    {
        // Si la commande est cd, traitez le premier argument différemment
        if (tokenIndex == 1 && ft_strcmp(commandList->tail->name, "cd") == 0) 
        {
            ft_process_cd_argument(commandList->tail, token);
            break;
        }

        printf("Launch ft_process_token_as_an_argument with argument number %d: named %s\n", tokenIndex, token);
        ft_process_token_as_an_argument(commandList, commandList->tail, token, tokenIndex);
        tokenIndex++;
    }
    return commandList->length;

    printf("The commandList length ath the end of ft_split_input_in_token_to_commandList is '%d'\n", commandList->length);
    printf("Printing commandList at the end of ft_split_input_in_token_to_commandList:\n");
    ft_print_commandList(commandList);
}

int ft_parse_and_add_to_commandList(t_commandList *commandList, char *input) 
{
    if (commandList == NULL)
    {
        perror("commandList head is NULL in ft_parse_and_add_to_commandList");
        return 1;
    }
    if (ft_split_input_in_token_to_commandList(commandList, input) > 0) 
    {
        return 0;
    } 
    else 
    {
        perror("Parsing failed");
        ft_destroy_command(commandList);
        return 1;
    }
}

int ft_launch_parsing_and_execution(t_commandList *commandList, char *input, t_env *envList, char **envp) 
{
    t_command *command;

    ft_initialize_commandList(commandList);

    if (ft_parse_and_add_to_commandList(commandList, input) == 0 && commandList->head != NULL) 
    {
        ft_print_commandList(commandList);

        command = commandList->head;

        if (ft_count_piped_commands(command) > 1)
        {
            ft_execute_piped_commands(commandList, command, ft_count_piped_commands(command), envList, envp);
        }
        
        else if (ft_execute_single_command(command, commandList, envList, envp) != 0) 
        {
            perror("Error executing command\n");
            ft_destroy_command(commandList);
            return 1;
        }
        
        return 0;
    } 
    else 
    {
        perror("ft_parse_and_add_to_commandList failed. commandList problem.\n");
        return 1;
    }
}
