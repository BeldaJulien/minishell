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
        if (shell->global_data != NULL)
            free(shell->global_data);
        free(shell);
    }
}

t_env *ft_initialize_environment(char **env)
{
    t_env *envList;
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

    return envList;
}

t_mini *ft_initialize_minishell(int ac, char **av, char **envp)
{
    t_mini *miniShell;
    
    miniShell = (t_mini *)malloc(sizeof(t_mini));
    if (miniShell == NULL) 
    {
        perror("Error initializing mini shell");
        exit(EXIT_FAILURE);
    }

    // Initialisation des membres de la structure mini_shell
    miniShell->fd_history = 0;
    miniShell->stdin_fd = dup(STDIN_FILENO);
    miniShell->stdout_fd = dup(STDOUT_FILENO);

    miniShell->commands = (t_commandList *)malloc(sizeof(t_commandList));
    ft_initialize_commandList(miniShell->commands);

    miniShell->global_data = (t_global *)malloc(sizeof(t_global));
    // Initialiser d'autres membres de global_data si nécessaire

    miniShell->error = NULL; // Initialisez à NULL ou faites une initialisation appropriée

    return miniShell;
}

void ft_execute_minishell(t_mini *shell, t_env *envList, char **envp)
{
    char *input;
    t_commandList commandList;

    ft_write_inputrc();

    while (ft_custom_prompt_msg(shell) && (shell->av != NULL))
    {
        input = ft_capture_input(shell);

        ft_manage_history(&shell, shell->av);

        if (ft_check_only_spaces(shell->av) == TRUE)
        {
            ft_destroy_current_shell(&shell);
            free(input);
            continue;
        }
        else if (ft_strcmp(shell->av, "") != 0)
        {
            ft_launch_parsing_and_execution(&commandList, input, envList, envp);
            ft_destroy_current_shell(&shell);
        }

        free(input);
    }
}




