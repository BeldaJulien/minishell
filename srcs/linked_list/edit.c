#include "minishell.h"

void ft_add_to_list(t_env **envlist, t_env *new_node)
{
    if (!envlist || !new_node)
        return;

    new_node->next = *envlist;
    *envlist = new_node;
}

int	ft_add_envVar_to_list(t_env **envlist, char *args)
{
	t_env	*new_node;

	new_node = ft_create_node(args);
	if (!new_node)
		return (0);
	if (!ft_is_in_lst(new_node->var, envlist))
		ft_add_to_list(envlist, new_node);
	else
		ft_replace_in_list(new_node, envlist);
	return (1);
}

void ft_replace_in_list(t_env *new_node, t_env **envlist)
{
	t_env	*tmp;

	tmp = ft_get_in_list(new_node->var, envlist);
	if (tmp)
		ft_free_env_node(new_node, tmp, new_node->value);
}


// Go through list to apply callback function on each element
void ft_iterate_through_list_to_apply_function(t_commandList  *head, void (*callback)(void *data))
{
    t_command  *current = head->head;
    
    while (current != NULL)
    {
        callback(current->data);
    current = current->next;
    }
}

int ft_compareString(void *data, void *target)
{
    char *str = (char *)data;
    char *key = (char *)target;
    return ft_strcmp(str, key);
}
