#include "minishell.h"

/*void execute_command_with_redirection(char *command, char *file) 
{
    int pid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Child process
        if (ft_single_redir_output == TRUE)
            int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else if (ft_double_redir_output == TRUE)
            int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Redirect standard output to file
        dup2(fd, STDOUT_FILENO);
        close(fd);

        // Execute the command
        execlp(command, command, (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, &status, 0);
    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
}
*/