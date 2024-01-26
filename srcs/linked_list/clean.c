#include "minishell.h"

void ft_free_list(t_commandList  *head)
{
    t_command  *current = head->head;
    
    while (current != NULL)
    {
        t_command  *next = current->next;
        free(current->data);
        free(current);

        current = next;
    }
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void ft_delete_list(t_env *envlist)
{
	t_env	*tmp;
	t_env	*node;

	tmp = envlist;
	if (envlist == NULL)
		return ;
	while (tmp != NULL)
	{
		free(tmp->name);
		free(tmp->value);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
}

void ft_free_node(t_command  *node)
{
    if (node != NULL)
    {
        free(node->data);

        if (node->prev != NULL)
            node->prev->next = node->next;
            
        if (node->next != NULL)
            node->next->prev = node->prev;

        free(node);
    }
}

void    ft_free_env_node(t_env *new_node, t_env *tmp, char *str)
{
	free(tmp->value);
	tmp->value = ft_strdup(str);
	free(new_node->name);
	free(new_node->value);
	free(new_node);
}


void ft_delete_node(t_commandList **head, t_command *node)
{
    if (*head == NULL || node == NULL)
        return;
    
    if ((*head)->head == node)
        (*head)->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;

    if (node->prev != NULL)
        node->prev->next = node->next;

    node->prev = NULL;
    node->next = NULL;

    free(node);
}

void ft_free_envList(t_env *envList)
{
    t_env *current; // Skip the initial empty node
    t_env *next;

    current = envList->next;
    while (current != NULL)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
}
