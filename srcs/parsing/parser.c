#include "minishell.h"

void ft_init_new_node(t_commandList *commandList, t_command *command, char *token)
{
    command->name = ft_strdup(token);
    command->data = NULL;
    command->args = (char **)malloc(sizeof(char *) * 2);
    if (command->args == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    command->args[0] = ft_strdup(token);
    command->args[1] = NULL;
    command->argCount = 1;
    command->redirectFile = NULL;
    command->fd[0] = -1;
    command->fd[1] = -1;
    command->next = NULL;
    command->prev = NULL;
    command->tokenType = ft_allocate_token_type(token);
    command->quoteType = ft_check_and_allocate_quote_type(token);
}

void ft_createNode_initNode_appendNodeToList(t_commandList *commandList, char *token) 
{
    t_command *command;
    
    command = ft_create_node_for_command();
    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    ft_init_new_node(commandList, command, token);
    printf("My new cute node contains command->name: %s\n", command->name);
    printf("My new cute node contains command->data: %p\n", command->data);
    printf("My new cute node contains command->args[0]: %s\n", command->args[0]);
    printf("My new cute node contains command->args[1]: %s\n", command->args[1]);
    printf("My new cute node contains command->argcount: %d\n", command->argCount);
    printf("My new cute node contains command->redirectfile: %s\n", command->redirectFile);
    printf("My new cute node contains command->fd[0]: %d\n", command->fd[0]);
    printf("My new cute node contains command->fd[1]: %d\n", command->fd[1]);
    printf("My new cute node contains command->next: %p\n", (void *)command->next);
    printf("My new cute node contains command->prev: %p\n", (void *)command->prev);
    printf("My new cute node contains command->tokenType: %d\n", command->tokenType);
    printf("My new cute node contains command->quoteType: %d\n", command->quoteType);
    ft_append_to_list(commandList, command);
}

void ft_process_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) 
{
    char **newArgs;

    if (command == NULL || token == NULL) 
    {
        perror("An error occurred in ft_process_argument: wrong input to process\n");
        return;
    }
    newArgs = (char **)malloc(sizeof(char *) * (argIndex + 2));
    if (newArgs == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
        
    command->args = newArgs;
    command->args[argIndex] = ft_strdup(token);
    command->args[argIndex + 1] = NULL;
    command->argCount++;
}

int ft_split_input_in_token_to_commandList(t_commandList *commandList, char *input) 
{
    char *token;
    int argIndex;
    
    argIndex = 0;
    token = ft_strtok(input, " ");
    if (token == NULL) 
    {
        perror("An error has occurred during input tokenization: Empty command\n");
        return 1;
    }
    ft_createNode_initNode_appendNodeToList(commandList, token);
    argIndex++;
    while ((token = ft_strtok(NULL, " ")) != NULL) 
    {
        if (ft_strcmp(token, "cd") == 0) 
        {
            ft_process_cd_argument(commandList->tail, token);
            break;
        }
        ft_process_argument(commandList, commandList->tail, token, argIndex);
        argIndex++;
    }
    return commandList->length;
}

int ft_parse_and_add_to_commandList(t_commandList *commandList, char *input) 
{
    if (commandList->head == NULL)
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
        // ft_print_commandList(commandList);

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
