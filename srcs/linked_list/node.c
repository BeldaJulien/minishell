#include "minishell.h"

t_command  *ft_get_previous_node(t_commandList  *head, t_command  *node)
{
    t_command *current;
    t_command  *previous;

    current = head->head;
    previous = NULL;

    while (current != NULL)
    {
        if(current == node)
            return previous;
        previous = current;
        current = current->next;
    }
    return NULL;
}

t_command  *ft_find_node(t_commandList  *head, void *target)
{
    t_command  *current;
    
    current = head->head;

    while (current != NULL)
    {
        if (ft_compareString(current->data, target) == 0)
            return current;
        current = current->next;
    }

    return NULL;
}

void    *ft_get_last_element_in_list(t_commandList *head)
{
    t_command *current;

	if (head == NULL)
        return NULL;
    
    current = head->head;

    while (current->next != NULL)
        current = current->next;

    return current->data;
}


void	ft_swap_nodes(t_env *tmp)
{
	char	*name;
	char	*value;

	if (ft_strcmp(tmp->name, tmp->next->name) > 0)
	{
		name = ft_strdup(tmp->next->name);
		value = ft_strdup(tmp->next->value);
		free(tmp->next->name);
		free(tmp->next->value);
		tmp->next->name = ft_strdup(tmp->name);
		tmp->next->value = ft_strdup(tmp->value);
		free(tmp->name);
		free(tmp->value);
		tmp->name = ft_strdup(name);
		tmp->value = ft_strdup(value);
		free(name);
		free(value);
	}
}

/*
t_env   *ft_find_envVar(t_env *envList, const char *targetName) 
{
    t_env *var = envList->head;

    while (var != NULL) {
        if (ft_strcmp(var->name, targetName) == 0) {
            return var;
        }
        var = var->next;
    }

    return NULL;
}
*/