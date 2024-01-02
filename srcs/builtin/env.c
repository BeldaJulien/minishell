#include "minishell.h"

int	env(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp != NULL)
	{
		if (tmp->var != NULL && tmp->value != NULL)
		{
			ft_putstr_fd(tmp->var, 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->value, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
