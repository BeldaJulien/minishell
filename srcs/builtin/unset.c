#include "minishell.h"

int ft_unset(t_env **envList, t_command *cmd) 
{
   
    t_env *check_node;
    t_env *prev_node;

    check_node = *envList;
    prev_node = NULL;

    if (!cmd || !cmd->args || !cmd->args[1] || !envList || !(*envList))
        return EXIT_FAILURE;

    while (check_node != NULL && ft_strcmp(cmd->args[1], check_node->name) != 0) 
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
        *envList = check_node->next; // Met à jour la tête de liste
    }

    // Libère la mémoire du nœud supprimé
    free(check_node->name);
    free(check_node->value);
    free(check_node);

    return EXIT_SUCCESS;
}