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
    if (!(ft_create_node_for_command())) 
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
    printf("My new cute node contains command->tokenType: %d\n", (int)command->tokenType);
    printf("My new cute node contains command->quoteType: %d\n", (int)command->quoteType);
    ft_append_to_list(commandList, command);
}

void ft_process_argument(t_commandList *commandList, t_command *command, char *token, int argIndex) 
{
    char **newArgs;
    int i;

    if (command == NULL || token == NULL) 
    {
        fprintf(stderr, "An error occurred: not enough arguments\n");
        return;
    }
    newArgs = (char **)malloc(sizeof(char *) * (argIndex + 2));
    if (newArgs == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (i < argIndex) 
    {
        newArgs[i] = command->args[i];
        i++;
    }
    newArgs[argIndex] = ft_strdup(token);
    newArgs[argIndex + 1] = NULL;
    command->args = newArgs;
    command->argCount++;
}

int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token;
    int argIndex;
    
    argIndex = 0;
    token = ft_strtok(input, " ");
    if (token == NULL) 
    {
        fprintf(stderr, "An error has occurred during input tokenization: Empty command\n");
        return 0;
    }
    ft_createNode_initNode_appendNodeToList(commandList, token);
    argIndex++;
    while ((token = ft_strtok(NULL, " ")) != NULL) 
    {
        if (argIndex == 1 && ft_strcmp(commandList->tail->name, "cd") == 0) 
        {
            ft_process_cd_argument(commandList->tail, token);
            break;
        }
        printf("Processing argument %d: %s\n", argIndex, token);
        ft_process_argument(commandList, commandList->tail, token, argIndex);
        argIndex++;
    }
    ft_process_argument(commandList, commandList->tail, NULL, argIndex);
    return commandList->length;
}

void ft_process_cd_argument(t_command *command, char *arg) 
{
    // Assurez-vous que la structure t_command est correctement initialisée avec les arguments
    command->args = malloc(2 * sizeof(char *));
    command->args[0] = ft_strdup(arg);
    command->args[1] = NULL;
}

int ft_launch_parsing(t_commandList *commandList, char *input, t_env *envList, char **envp)
{
    t_command *command;
    ft_initialize_commandList(commandList);

    if (ft_split_arg(commandList, input) > 0) 
    {
        
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
