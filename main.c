#include "minishell.h"

int g_exit_code = 0;

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

void ft_write_inputrc(void)
{
    int fd;
    char *home;

    home = getenv("HOME");
    home = ft_strjoin(home, "/.inputrc");
    if (home == NULL) {
        perror("ft_strjoin");
        exit(EXIT_FAILURE);
    }
    fd = open(home, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) 
    {
        perror("open");
        free(home);
        exit(EXIT_FAILURE);
    }
    const char *content = "set echo-control-characters Off\n";
    ssize_t bytes_written = write(fd, content, strlen(content));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        free(home);
        exit(EXIT_FAILURE);
    }
    close(fd);
    free(home);
}

int main(int ac, char **av, char **envp)
{
    t_mini shell;
    t_env envList;
    
    ft_initialize_minishell(&shell, ac, av, envp);
    ft_initialize_environment(&envList, envp);

    if (ac > 1)
    {
        perror("CHAOS, there are too many arguments");
        return 1;
    }

    ft_execute_minishell(&shell, &envList, envp);

    ft_free_envList(&envList);
    ft_exit_shell(&shell);
    return 0;
}