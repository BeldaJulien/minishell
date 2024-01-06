#include "minishell.h"

int ft_unset(t_env **env_list, t_command *cmd) 
{
	t_env *check_node;
    t_env *prev_node;

    if (!cmd || !env_list || !(*env_list))
        return EXIT_FAILURE;

    check_node = *env_list;
    prev_node = NULL;

    while (check_node != NULL && ft_strcmp(cmd->name, check_node->name) != 0) 
	{
        prev_node = check_node;
        check_node = check_node->next;
    }

    if (check_node == NULL) {
        return EXIT_FAILURE;
    }

    if (prev_node != NULL) {
        prev_node->next = check_node->next;
    } else {
        // Si le nœud à supprimer est en tête de liste
        *env_list = check_node->next;
    }

    free(check_node->name);
    free(check_node->value);
    free(check_node);

    return EXIT_SUCCESS;
}
