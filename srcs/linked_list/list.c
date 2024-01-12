#include "minishell.h"

int ft_is_empty_list(t_commandList    *head)
{
    if (head == NULL)
        return 1;
    else 
        return 0;
}


int	ft_is_in_list(char	*var, t_env **envlist)
{
	t_env	*tmp;
	
	tmp = *envlist;
	if (tmp == NULL || var == NULL)
		return (0);
	while (tmp != NULL && ft_strcmp(tmp->name, var) != 0)
		tmp = tmp->next;
	return (tmp != NULL);
}

int ft_get_commandList_size(t_commandList  *head)
{
    int size = 0;
    t_command  *current = head->head;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

// Dans le fichier source linked_list.c (ou le fichier approprié)
t_env	*ft_get_in_list(char *var, t_env **envlist)
{
	t_env	*tmp;

	tmp = *envlist;
	if (tmp == NULL || var == NULL)
		return (NULL);
	while (tmp != NULL && ft_strcmp(tmp->name, var) != 0)
		tmp = tmp->next;
	if (tmp)
		return (tmp);
	return (NULL);
}

int	ft_get_envList_size(t_env **list)
{
	int		i;
	t_env	*tmp;

	tmp = *list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}


// adapt casting depending data type to store in list
void ft_printGeneric(void *data)
{
    char *str = (char *)data;
    printf("%s\n", str);
}

