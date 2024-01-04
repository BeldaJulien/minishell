#include "minishell.h"

int	ft_unset(t_env *env_list, t_command *cmd)
{
	t_env	*check_node;
	t_env	*prev_node;

	check_node = env_list;
	if (!cmd || env_list == NULL)
		return (EXIT_FAILURE);
	while (ft_strcmp(cmd->name, check_node->name) != 0 && cmd->name)
	{
		prev_node = check_node;
		check_node = check_node->next;
		if (check_node == NULL)
			return (EXIT_FAILURE);
	}
	prev_node->next = check_node->next;
	free(check_node->name);
	free(check_node->value);
	free(check_node);
	return (EXIT_SUCCESS);
}
