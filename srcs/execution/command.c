#include "minishell.h"

/* void	ft_execute_command(t_command *command, t_env *envList)
{
	int		init_stdout;
	int		init_stdin;

	if (command == NULL)
	{
		fprintf(stderr, "Error: Trying to execute a NULL command\n");
		return ;
	}
	printf("Executing command: %s\n", command->name);
	init_stdout = dup(STDOUT_FILENO);
	init_stdin = dup(STDIN_FILENO);
	if (command->fdread >= 3)
		dup2(command->fdread, STDIN_FILENO);
	if (command->fdwrite >= 3)
		dup2(command->fdwrite, STDOUT_FILENO);
	if (ft_is_builtin(command) == 1)
		ft_execute_builtin(command, &envList);
	else if (ft_is_builtin(command) == 127)
		g_exit_code = 127;
	// else
	// 	ft_execute_external_command(command, commandList, envList);
	if (command->fdread >= 3)
		close(command->fdread);
	if (command->fdwrite >= 3)
		close(command->fdwrite);
	dup2(init_stdout, STDOUT_FILENO);
	dup2(init_stdin, STDIN_FILENO);
	close(init_stdout);
	close(init_stdin);
	printf("Execution complete\n");
} */


void ft_execute_external_command(t_command *command, t_commandList *commandList, char **envp)
{
    
    
    char *path = getenv("PATH");
    char *full_path = ft_lookfor_command_and_build_path(path, commandList);

    if (full_path != NULL)
    {
        pid_t pid;
        int status;

        pid = fork();
        if (pid == 0)
        {
            if (execve(full_path, (command->args), envp) == -1) 
            {
                perror("Erreur lors de l'exécution de la commande");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid == -1) 
        {
            perror("Erreur lors de la création du processus enfant");
            exit(EXIT_FAILURE);
        }
        else 
        {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) 
            {
                int exitStatus = WEXITSTATUS(status);
                printf("Le processus enfant s'est terminé avec le code de sortie : %d\n", exitStatus);
            }
            else if (WIFSIGNALED(status)) 
            {
                int signalNumber = WTERMSIG(status);
                printf("Le processus enfant a été interrompu par le signal : %d\n", signalNumber);
            }
            free(full_path);
        }
    }
    else 
    {
        fprintf(stderr, "Command not found in PATH: %s\n", command->name);
    }
}

