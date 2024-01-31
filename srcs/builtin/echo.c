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
void ft_echo_args(t_command *cmd) 
{
    int i;
    
    i = 1;

    while (cmd->args[i] != NULL) 
    {
        ft_handle_argument(cmd->args[i]);

        if (cmd->args[i + 1] != NULL)
            ft_handle_space();

        i++;
    }
}

void print_error_message(char *message)  
{
    write(STDERR_FILENO, message, ft_strlen(message));
}

// Fonction principale pour la commande echo
int echo(t_command *cmd, int g_exit_code) 
{
    char *message;
    int suppressNewline;

    (void)g_exit_code;
    message = "An error occurred in echo : not enough arguments\n";
    suppressNewline = 0;

    if (cmd == NULL || cmd->args == NULL) 
    {
        print_error_message(message);
        return 1;
    }

    if (cmd->args[1] != NULL && ft_strcmp(cmd->args[1], "-n") == 0) 
    {
        suppressNewline = 1;
        ft_echo_args(cmd);
    } else {
        ft_echo_args(cmd);
        if (!suppressNewline) 
            write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}