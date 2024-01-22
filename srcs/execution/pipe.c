#include "minishell.h"

void ft_execute_command_with_pipe(t_command *command, t_env *envList, char **envp) 
{
    (void)envList;
    (void)envp; 

    if (execvp(command->name, command->args) == -1) 
    {
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }
}

void ft_execute_piped_commands(t_commandList *commandList, t_command *commands, int num_commands, t_env *envList, char **envp) 
{
    int pipes[num_commands - 1][2];
    pid_t child_pids[num_commands];
    char *full_path;
    char *path;

    path = getenv("PATH");
    full_path = ft_lookfor_command_and_build_path(path, commandList);

    // Créer les pipes
    ft_create_pipes_array(pipes, num_commands - 1);

    // Lancer les processus enfants
    ft_launch_child_processes(commands, num_commands, pipes, child_pids, envList, envp);

    // Fermer les descripteurs de fichiers des pipes dans le processus parent
    ft_close_pipes(pipes, num_commands - 1);

    // Attendre que tous les processus enfants se terminent
    ft_wait_for_child_processes_to_end(child_pids, num_commands, full_path, commands->args, envp);
}
