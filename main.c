#include "minishell.h"

int g_exit_code = 0;

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
    t_env *envList;
    t_commandList commandList;
    
    
    (void)av;
    if (ac > 1) {
        fprintf(stderr, "CHAOS, there are too many arguments\n");
        return 1;
    }
    envList = NULL;
    envList = ft_initialize_environment(envp);
    
    ft_initialize_all(&shell, envp);

    while (1) 
    {
        // TO DO add signals here
        ft_custom_prompt_msg(&shell);

        if (shell.av == NULL) {
            printf("Stop shell\n");
            break;
        }

        ft_manage_history(&shell, shell.av);

        if (ft_check_only_spaces(shell.av) == TRUE) {   
            ft_destroy_current_shell(&shell);
            continue;
        } 
        else if (ft_strcmp(shell.av, "") != 0) {
            ft_launch_parsing(&commandList, shell.av, &envList, envp);
            ft_destroy_current_shell(&shell);
        }
    }
    ft_exit_shell(&shell);
    return 0;
}
