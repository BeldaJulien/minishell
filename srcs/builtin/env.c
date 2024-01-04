#include "minishell.h"

void ft_display_envList(t_env *envList) 
{
	t_env *current;

	current = envList;
    while (current != NULL) 
	{
        printf("%s=%s\n", current->name, current->value);
        current = current->next;
    }
}

int	env(t_env *envList)
{
	ft_display_envList(envList);
	return (0);
}

/*
int	env(t_env **envList)
{
	t_env	*tmp;

	tmp = *envList;
	while (tmp != NULL)
	{
		if (tmp->name != NULL && tmp->value != NULL)
		{
			ft_putstr_fd(tmp->name, 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->value, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
*/