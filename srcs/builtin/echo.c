#include "minishell.h"

// Fonction pour gérer l'affichage de chaque argument après l'expansion
void ft_handle_argument(char *arg) 
{
    char *expanded_arg;
    
    expanded_arg = ft_expand_env_variables(arg);

    if (expanded_arg == NULL) 
    {
        perror("Error expanding environment variables\n");
        exit(1);
    }

    write(STDOUT_FILENO, expanded_arg, ft_strlen(expanded_arg));

    free(expanded_arg);
}

// Fonction pour gérer l'affichage de l'espace entre les arguments
void ft_handle_space() 
{
    write(STDOUT_FILENO, " ", 1);
}

// Fonction principale pour l'affichage des arguments de la commande echo
void ft_echo_args(char **args, int g_exit_code) 
{
    if (args == NULL) 
        return;

    (void)g_exit_code;
    int i = 1;

    while (args[i] != NULL) 
    {
        char *expanded_arg = ft_expand_env_variables(args[i]);

        if (expanded_arg != NULL) 
        {
            // CHEATING HERE sent in void ft_process_char(char *result, int *j, char *command, int *i) 
            // try tests and bugs ?
            // write(STDOUT_FILENO, expanded_arg, ft_strlen(expanded_arg));
            free(expanded_arg);
        } 
        else 
        {
            perror("Error expanding environment variables\n");
            exit(1);
        }

        if (args[i + 1] != NULL)
            ft_handle_space();

        i++;
    }
}

void print_error_message(char *message)  
{
    write(STDERR_FILENO, message, ft_strlen(message));
}

// Fonction principale pour la commande echo
int echo(char **args, int g_exit_code) 
{
    char *message = "An error occurred in echo: not enough arguments\n";
    int suppressNewline = 0;

    if (args == NULL || args[1] == NULL) 
    {
        write(STDERR_FILENO, message, strlen(message));
        return 1;
    }

    if (ft_strcmp(args[1], "-n") == 0)
    {
        suppressNewline = 1;
        ft_echo_args(args, g_exit_code);
    } 
    else 
    {
        ft_echo_args(args, g_exit_code);
        if (!suppressNewline) 
            write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}