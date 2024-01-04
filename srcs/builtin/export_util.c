#include "minishell.h" 

int	ft_is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	ft_is_only_digit(char *str)
{
    while (*str && ft_isdigit(*str))
        str++;
    if (!*str)
        return (TRUE);
    return (FALSE);
}
void ft_print_export_list(t_env **envlist)
{
	t_env	*tmp;
	t_env	*sort_list;

	sort_list = ft_sort_list_export(envlist);
	tmp = sort_list;
	while (tmp != NULL)
	{
		if (tmp->name != NULL)
		{
			ft_putstr_fd(tmp->name, 1);
			write(1, "=", 1);
			ft_putstr_fd(tmp->value, 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	ft_delete_list(sort_list);
}

t_env	*ft_sort_list_export(t_env **envlist)
{
	t_env	*tmp;
	t_env	*sort_list;
	int		i;

	sort_list = ft_envlist_duplicate(envlist);
	i = ft_count_list(&sort_list);
	tmp = sort_list;
	while (i > 0)
	{
		tmp = sort_list;
		while (tmp->next != NULL)
		{
			ft_swap_nodes(tmp);
			tmp = tmp->next;
		}
		i--;
	}
	return (sort_list);
}

int	ft_is_in_lst(char	*var, t_env **envlist)
{
	t_env	*tmp;
	
	tmp = *envlist;
	if (tmp == NULL || var == NULL)
		return (0);
	while (tmp != NULL && ft_strcmp(tmp->name, var) != 0)
		tmp = tmp->next;
	return (tmp != NULL);
}

void	replace_in_lst(t_env *new_node, t_env **envlist)
{
	t_env	*tmp;

	tmp = ft_get_in_list(new_node->name, envlist);
	if (tmp)
		ft_free_env_node(new_node, tmp, new_node->value);
}

int	ft_add_var_to_list(t_env **envlist, char *args)
{
	t_env	*new_node;

	new_node = ft_create_node(args);
	if (!new_node)
		return (0);
	if (!ft_is_in_lst(new_node->name, envlist))
		ft_add_to_list(envlist, new_node);
	else
		ft_replace_in_list(new_node, envlist);
	return (1);
}

t_env	*ft_create_node(char *var_array)
{
	t_env	*new_node;
	int		i;

	new_node = malloc(sizeof(t_env));
	i = 0;
	if (new_node)
	{
		while (var_array[i] != '=' && var_array[i] != '\0')
			i++;
		new_node->name = ft_substr(var_array, 0, i);

		if (var_array[i] == '\0')
		{
			// Cas où var_array ne contient pas le caractère '='
			new_node->value = ft_strdup("");
		}
		else
		{
			i++; // Ignorer le caractère '='
			new_node->value = ft_strdup(var_array + i);
		}

		new_node->next = NULL;
		return new_node;
	}
	return NULL;
}