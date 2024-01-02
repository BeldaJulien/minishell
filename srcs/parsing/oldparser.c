/* int ft_split_arg(t_commandList *commandList, char *input) 
{
    char *token = ft_strtok(input, " ");

    while (token != NULL) 
    {
        t_command *newCommand = ft_create_node_for_command();

        newCommand->name = ft_strdup(token);

        if (newCommand == NULL) 
        {
            perror("CHAOS, error allocating memory");
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }
        if (newCommand->name == NULL) 
        {
            perror("CHAOS, error allocating memory");
            free(newCommand);
            ft_destroy_command(commandList);
            exit(EXIT_FAILURE);
        }
        if (commandList->head == NULL) 
        {
            commandList->head = newCommand;
            commandList->tail = commandList->head;
        } else 
        {
            ft_appendToList(commandList, newCommand);
            commandList->tail = commandList->tail->next;
        }
        commandList->length++;
        token = ft_strtok(NULL, " ");
    }
    return commandList->length;
} 

int ft_launch_parsing(t_commandList *commandList, char *input, t_env **envList) 
{
    ft_initialize_commandList(commandList);

    if (ft_split_arg(commandList, input) > 0) 
    {
        if (commandList != NULL && commandList->head != NULL) 
        {
            ft_print_list(commandList, ft_print_command);
            t_command *cmd = commandList->head;

            // Utilisez la liste d'arguments directement à partir de ft_split_arg
            cmd->args = commandList->head->args;

            if (ft_is_builtin(cmd)) 
            {
                printf("Parsing succeeded. Commands:\n");
                ft_execute_builtin(cmd, envList);
            } 
            else 
                printf("Executing external command:\n");
        } 
        else 
            fprintf(stderr, "Error: commandList or its head is NULL\n");
        return 1;
    } 
    else 
    {
        perror("Parsing failed");
        ft_destroy_command(commandList);  // Libération mémoire en cas d'échec
        return 0;
    }
}
 */









/* #include "minishell.h"

int ft_split_command(t_commandList *commandList, char *command, char *arguments) 
{
    t_command *newCommand = malloc(sizeof(t_command));
    if (newCommand == NULL) {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    newCommand->name = ft_strdup(command);
    newCommand->args = NULL;

    // Code pour traiter les arguments (si présents)
    if (arguments != NULL && *arguments != '\0') {
        // Allouer de l'espace pour stocker les arguments
        newCommand->args = ft_split_arg_list(arguments);
    }

    newCommand->next = NULL;

    // Ajouter la nouvelle commande à la liste
    if (commandList->head == NULL) {
        commandList->head = newCommand;
        commandList->tail = commandList->head;
    } else {
        commandList->tail->next = newCommand;
        commandList->tail = newCommand;
    }

    commandList->length++;

    return commandList->length;
}



int ft_split_arg(t_commandList *commandList, char *input) 
{
    // Recherche du premier espace dans la chaîne d'entrée
    char *space = ft_strchr(input, ' ');

    if (space == NULL) {
        // Pas d'espace, la chaîne entière est considérée comme une commande sans arguments
        return ft_split_command(commandList, input, NULL);
    } else {
        // Séparation de la commande et des arguments
        *space = '\0';  // Remplace l'espace par un caractère nul pour isoler la commande
        char *command = input;
        char *arguments = space + 1;  // Les arguments commencent après l'espace

        // Si la commande est "echo", vérifiez si les arguments commencent par "-n"
        if (strcmp(command, "echo") == 0 && arguments[0] == '-' && arguments[1] == 'n') {
            return ft_split_command(commandList, command, arguments);
        } else {
            return ft_split_command(commandList, command, arguments);
        }
    }
}

int ft_launch_parsing(t_commandList *commandList, char *input, t_env **envList) 
{
    ft_initialize_commandList(commandList);

    // Copier la chaîne d'entrée avant de la traiter avec strtok
    char *inputCopy = strdup(input);
    if (inputCopy == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }

    // Séparer la commande et les arguments en utilisant ft_split_command
    char *command = strtok(inputCopy, " ");
    char *arguments = strtok(NULL, "");  // Utiliser NULL pour récupérer le reste de la chaîne

    if (ft_split_command(commandList, command, arguments) > 0) 
    {
        if (commandList != NULL && commandList->head != NULL) 
        {
            ft_print_list(commandList, ft_print_command);
            t_command *cmd = commandList->head;

            if (ft_is_builtin(cmd)) 
            {
                //printf("Parsing succeeded. Commands:\n");
                ft_execute_builtin(cmd, envList);
            } 
            else 
                printf("Executing external command:\n");
        } 
        else 
            fprintf(stderr, "Error: commandList or its head is NULL\n");

        // Libérer la mémoire utilisée pour la copie de la chaîne
        free(inputCopy);

        return 1;
    } 
    else 
    {
        perror("Parsing failed");
        ft_destroy_command(commandList);  // Libération mémoire en cas d'échec

        // Libérer la mémoire utilisée pour la copie de la chaîne
        free(inputCopy);

        return 0;
    }
}

char **ft_split_arg_list(char *input) {
    char **args = NULL;
    size_t count = 0;

    char *token = ft_strtok_quoted(input, " ");
    while (token != NULL) {
        args = realloc(args, sizeof(char *) * (count + 1));
        if (args == NULL) {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }

        args[count] = ft_strdup(token);
        if (args[count] == NULL) {
            perror("CHAOS, error allocating memory");
            exit(EXIT_FAILURE);
        }

        count++;
        token = ft_strtok_quoted(NULL, " ");
    }

    args = realloc(args, sizeof(char *) * (count + 1));
    if (args == NULL) {
        perror("CHAOS, error allocating memory");
        exit(EXIT_FAILURE);
    }
    args[count] = NULL;

    return args;
}

char *ft_strtok_quoted(char *str, const char *delim) {
    static char *input = NULL;
    if (str != NULL) {
        input = str;
    }

    if (input == NULL || *input == '\0') {
        return NULL;
    }

    char *token_start = input;
    char quote = '\0';

    while (*input != '\0' && (quote != '\0' || strchr(delim, *input) == NULL)) {
        if (*input == '\"' || *input == '\'') {
            if (quote == '\0') {
                quote = *input;
            } else if (quote == *input) {
                quote = '\0';
            }
            input++;
        } else {
            input++;
        }
    }

    if (*input != '\0') {
        *input = '\0';
        input++;
    }

    return token_start;
} */