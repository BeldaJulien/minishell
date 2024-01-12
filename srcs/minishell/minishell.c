/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:45:17 by bat               #+#    #+#             */
/*   Updated: 2024/01/12 16:06:57 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit_shell(t_mini *shell)
{
    if (shell->av)
        free(shell->av);
}

void ft_initialize_commandList(t_commandList *commandList) 
{
    if (commandList == NULL) 
    {
        fprintf(stderr, "Error: NULL pointer in ft_init_commandList\n");
        exit(EXIT_FAILURE);
    }

    commandList->head = NULL;
    commandList->tail = NULL;
    commandList->length = 0;
}

t_env *ft_initialize_environment(char **env)
{
    t_env *envList = NULL;
    t_env *new_node;
    char **var_array;
    int i = 0;

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

void ft_initialize_minishell(t_mini *shell)
{
    shell->av = NULL;
    shell->numberOfCommands = 0;
    shell->fd_history = 0;
    shell->status = 0;
    shell->stdin_fd = dup(STDIN_FILENO);
    shell->stdout_fd = dup(STDOUT_FILENO);
    shell->commands = NULL;
    shell->child = malloc(sizeof(t_global));
    if (shell->child == NULL) {
        perror("Failed to allocate memory for shell->child");
        exit(EXIT_FAILURE);
    }
    shell->exec = malloc(sizeof(t_global));  // Initialisez-le de la même manière si nécessaire
    if (shell->exec == NULL) {
        perror("Failed to allocate memory for shell->exec");
        exit(EXIT_FAILURE);
    }
    shell->error = NULL;  // Assurez-vous de l'initialiser correctement si nécessaire
    ft_write_inputrc();
}

t_env *ft_initialize_all(t_mini *shell, char **envp, t_env *envList)
{
    //t_commandList commandList;
    
    envList = ft_initialize_environment(envp);
    ft_initialize_minishell(shell);
    //ft_initialize_commandList(&commandList);

    return envList;
}