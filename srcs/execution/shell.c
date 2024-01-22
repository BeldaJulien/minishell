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
    t_mini *shell;
    
    (void)ac;
    (void)av;
    (void)envp;
    shell = (t_mini *)malloc(sizeof(t_mini));
    if (shell == NULL) 
    {
        perror("Error initializing mini shell");
        exit(EXIT_FAILURE);
    }

    // Initialisation des membres de la structure mini_shell
    shell->av = NULL;
    shell->fd_history = 0;
    shell->stdin_fd = dup(STDIN_FILENO);
    shell->stdout_fd = dup(STDOUT_FILENO);

    shell->commands = (t_commandList *)malloc(sizeof(t_commandList));
    ft_initialize_commandList(shell->commands);

    // Initialiser d'autres membres de global_data si nécessaire

    shell->error = NULL; // Initialisez à NULL ou faites une initialisation appropriée

    return shell;
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




