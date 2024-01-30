#include "minishell.h"

int g_exit_code = 0;

/*
char *ft_capture_input(void) 
{
    char input[MAX_INPUT_SIZE];
    int input_length;

    printf("Entrez votre commande : ");
    
    // Utilisation de read pour lire l'entrée utilisateur
    input_length = read(STDIN_FILENO, input, sizeof(input));
    if (input_length == -1) 
    {
        perror("Erreur lors de la lecture de l'entrée utilisateur");
        exit(EXIT_FAILURE);
    }

    // Supprimer le caractère de nouvelle ligne s'il est présent
    if (input_length > 0 && input[input_length - 1] == '\n') 
    {
        input[input_length - 1] = '\0';
    }

    // À ce stade, 'input' contient la ligne de commande entrée par l'utilisateur
    printf("Vous avez entré : %s\n", input);

    return ft_strdup(input);  // N'oubliez pas de libérer la mémoire après usage
}
*/

int main(int ac, char **av, char **envp)
{
    t_mini shell;
    t_env *envList;
    t_commandList commandList;

    (void)av;
    if (ac > 1)
    {
        perror("CHAOS, there are too many arguments\n");
        return 1;
    }
    envList = NULL;
    ft_initialize_minishell(&shell);
    ft_initialize_environment(&envList, envp);
    ft_execute_minishell(&commandList, &shell, envList, envp);
    ft_free_envList(envList);
    ft_exit_shell(&shell);
    return 0;
}