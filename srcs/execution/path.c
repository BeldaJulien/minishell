#include "minishell.h"

char *ft_build_full_path(t_commandList *commandList) 
{
    char *path;
    
    path = getenv("PATH");
    return ft_lookfor_command_and_build_path(path, commandList);
}

void ft_execute_command_with_absolute_path(t_command *command)
{
    if (execve(command->name, command->args, NULL) == -1)
    {
            perror("Error executing absolute path");
            exit(EXIT_FAILURE);  
    }
}

void ft_execute_command_with_relative_path(t_command *command) 
{
    char *current_path;
    char *full_path;
    char *path_ptr;
    char *command_name;
    
    current_path = getcwd(NULL, 0);
    if (current_path == NULL) {
        perror("Error executing relative path");
        exit(EXIT_FAILURE);
    }

    full_path = malloc(strlen(current_path) + strlen(command->name) + 2);
    if (full_path == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    path_ptr = full_path;
    while (*current_path != '\0') {
        *path_ptr = *current_path;
        path_ptr++;
        current_path++;
    }
    *path_ptr = '/';
    path_ptr++;

    command_name = command->name;
    while (*command_name != '\0') 
    {
        *path_ptr = *command_name;
        path_ptr++;
        command_name++;
    }
    *path_ptr = '\0';

    if (access(full_path, X_OK) == 0) 
    {
        if (execve(full_path, command->args, NULL) == -1) {
            perror("Erreur lors de l'exécution de la commande");
            exit(EXIT_FAILURE);
        }
    } else 
    {
        // Utilisation de printf pour afficher le message d'erreur
        printf("Command not found: %s\n", full_path);
        exit(EXIT_FAILURE);
    }

    free(current_path);
    free(full_path);
}


void ft_execute_command_with_path(t_command *command) 
{

    if (command->name[0] == '/') 
    {
        ft_execute_command_with_absolute_path(command);  
    } else if (command->name[0] == '.') 
    {
        ft_execute_command_with_relative_path(command);   
    } 
}

char *ft_lookfor_command_and_build_path(char *path, t_commandList *commandList) 
{
    char *token;
    char fullPath[MAX_PATH_LENGTH];

    // Faites une copie du chemin d'origine
    char *originalPath = ft_strdup(path);

    token = ft_strtok((char *)originalPath, ":");
    while (token != NULL) 
    {
        t_command *currentCommand = commandList->head; // Réinitialisez le pointeur ici

        while (currentCommand != NULL) 
        {
            ft_strcpy(fullPath, token);
            ft_strcat(fullPath, "/");
            ft_strcat(fullPath, currentCommand->name);
            if (access(fullPath, X_OK) == 0) 
            {
                printf("Command '%s' found: %s\n", currentCommand->name, fullPath);
                
                // Réinitialisez le chemin après utilisation
                free(originalPath);
                return ft_strdup(fullPath);
            }
            currentCommand = currentCommand->next;
        }
        // Passez au jeton suivant
        token = ft_strtok(NULL, ":");
    }

    // Restaurez le chemin d'origine après utilisation
    free(originalPath);
    printf("Commandes non trouvées dans ft_lookfor_command_and_build_path\n");
    return NULL;
}
