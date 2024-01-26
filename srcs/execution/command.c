#include "minishell.h"

int ft_execute_single_command(t_command *command, t_commandList *commandList, t_env *envList, char **envp) 
{
    if (command->tokenType == COMMAND_TYPE) 
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

void ft_process_command(t_commandList *commandList, char *token) 
{
    t_command *command;
    
    command = ft_create_node_for_command();
    if (command == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    command->name = ft_strdup(token);
    command->tokenType = ft_allocate_token_type(token);
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

t_command *ft_init_new_command(char *name) 
{
    t_command *newCommand;
    
    newCommand = (t_command *)malloc(sizeof(t_command));
    
    if (newCommand == NULL) 
    {
        perror("Memory allocation failed in ft_init_new_command");
        exit(EXIT_FAILURE);
    }

    // Initialisation des champs de la structure
    newCommand->name = strdup(name);
    newCommand->data = NULL; // À ajuster en fonction de l'utilisation prévue de `data`
    newCommand->args = NULL;
    newCommand->argCount = 0;
    newCommand->redirectFile = NULL;
    newCommand->fd[0] = newCommand->fd[1] = -1;
    newCommand->next = NULL;
    newCommand->prev = NULL;
    newCommand->tokenType = COMMAND_TYPE; // Assurez-vous d'ajuster cela si nécessaire
    newCommand->quoteType = NORMAL;/* Assurez-vous d'ajuster cela en fonction de votre logique */

    return newCommand;
}

void ft_add_argument_to_command(t_command *command, const char *argument) 
{
    int i;
    char **newArgs;
    
    newArgs = (char **)malloc((command->argCount + 1) * sizeof(char *));
    if (!newArgs) perror("Memory allocation failed in ft_add_argument_to_command"), exit(EXIT_FAILURE);

    i = 0;
    while (i < command->argCount) 
    {
        if (!(newArgs[i] = strdup(command->args[i])))
            perror("Memory allocation failed in ft_add_argument_to_command"), exit(EXIT_FAILURE);
        i++;
    }

    if (!(newArgs[command->argCount] = strdup(argument)))
        perror("Memory allocation failed in ft_add_argument_to_command"), exit(EXIT_FAILURE);

    i = 0;
    while (i < command->argCount) 
    {
        free(command->args[i]);
        i++;
    }
    free(command->args);

    command->args = newArgs;
    command->argCount++;
}
