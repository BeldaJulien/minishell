#include "minishell.h"

pid_t ft_create_child_process() 
{
    pid_t child_pid;
    
    child_pid = fork();

    if (child_pid < 0) {
        perror("Error forking process");
        exit(EXIT_FAILURE);
    }

    return child_pid;
}

void ft_launch_child_processes(t_command *commands, int num_commands, int pipes[][2], pid_t child_pids[], t_env *envList, char **envp) 
{
    int i;
    
    i = 0;
    while (i < num_commands)
    {
        child_pids[i] = ft_create_child_process();

        if (child_pids[i] == 0) {
            // Processus enfant
            ft_configure_child_process(commands, num_commands, i, pipes, envList, envp);
            exit(EXIT_SUCCESS);
        }

        i++;
    }
}

void ft_execute_child_process(char *full_path, char **args, char **envp)
 {
    if (execve(full_path, args, envp) == -1) 
    {
        perror("Erreur lors de l'exécution de la commande");
        exit(EXIT_FAILURE);
    }
}

void ft_wait_for_child_processes_to_end(pid_t *child_pids, int num_commands, char *full_path, char **args, char **envp) 
{
    int i;

    i = 0;
    while (i < num_commands)
    {
        child_pids[i] = ft_create_child_process();
         if (child_pids[i] == 0)
        {
            // Code du processus enfant ici
            printf("Je suis le processus enfant avec PID : %d\n", getpid());
            ft_execute_child_process(full_path, args, envp);
            // Assurez-vous de sortir du bloc if après le traitement
            exit(EXIT_SUCCESS);
        }
        i++;
    }
    i = 0;
    while (i < num_commands)
    {
        ft_wait_for_child_process(child_pids[i]);
        i++;
    }
}

void ft_wait_for_child_process(pid_t pid) 
{
    int status;
    int exitStatus;
    int signalNumber;

    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) 
    {
        exitStatus = WEXITSTATUS(status);
        printf("Le processus enfant s'est terminé avec le code de sortie : %d\n", exitStatus);
    } 
    else if (WIFSIGNALED(status)) 
    {
        signalNumber = WTERMSIG(status);
        printf("Le processus enfant a été interrompu par le signal : %d\n", signalNumber);
    }
}

void ft_configure_child_process(t_command *commands, int num_commands, int index, int pipes[][2], t_env *envList, char **envp) 
{
    if (index > 0) {
        // Rediriger l'entrée depuis le pipe précédent
        dup2(pipes[index - 1][0], STDIN_FILENO);
    }

    if (index < num_commands - 1) {
        // Rediriger la sortie vers le pipe suivant
        dup2(pipes[index][1], STDOUT_FILENO);
    }

    // Fermer tous les descripteurs de fichiers des pipes
    ft_close_pipes(pipes, num_commands - 1);

    // Exécuter la commande avec pipe
    ft_execute_command_with_pipe(&commands[index], envList, envp);
}

