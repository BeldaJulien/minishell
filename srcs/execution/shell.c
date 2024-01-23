#include "minishell.h"

void ft_exit_shell(t_mini *shell)
{
    if (shell != NULL) 
    {
        if (shell->av != NULL)
            free(shell->av);
        // Mettez à jour en conséquence si vous utilisez t_command au lieu de t_commandList
        if (shell->commands != NULL)
            ft_destroy_commandList(shell->commands);
        free(shell);
    }
}

void ft_initialize_environment(t_env *envList, char **env)
{
    t_env *new_node;
    char **var_array;
    int i;

    i = 0;
    envList = NULL;
    var_array = ft_env_duplicate(env);

    while (var_array[i])
    {
        new_node = ft_create_node_for_args(var_array[i]);
        ft_add_to_list(&envList, new_node);
        i++;
    }

    ft_free_array(var_array);
}

void ft_initialize_minishell(t_mini *shell, int ac, char **av, char **envp)
{
    if (shell == NULL) 
    {
        perror("Error initializing mini shell");
        exit(EXIT_FAILURE);
    }

    (void)ac;
    (void)av;
    (void)envp;

    shell->av = NULL;
    shell->fd_history = 0;
    shell->stdin_fd = dup(STDIN_FILENO);
    shell->stdout_fd = dup(STDOUT_FILENO);
    shell->error = NULL;

    shell->commands = (t_commandList *)malloc(sizeof(t_commandList));
    if (shell->commands == NULL) 
    {
        perror("Error initializing mini shell: Memory allocation failure");
        exit(EXIT_FAILURE);
    }

    ft_initialize_commandList(shell->commands);

}

void ft_execute_minishell(t_mini *shell, t_env *envList, char **envp)
{
    char *input;
    t_commandList commandList;

    ft_write_inputrc();

    while (1)
    {
        // TO DO add signals here
        ft_custom_prompt_msg(shell);

        if (shell->av == NULL) 
        {
            printf("Stop shell\n");
            break;
        }

        input = ft_capture_input();

        ft_manage_history(shell, input);

        if (ft_check_if_only_spaces(input) == TRUE)
        {
            ft_destroy_current_shell(shell);
            free(input);
            continue;
        }
        else if (ft_strcmp(input, "") != 0)
        {
            ft_launch_parsing_and_execution(&commandList, input, envList, envp);
            ft_destroy_current_shell(shell);
        }

        free(input);
    }
}




