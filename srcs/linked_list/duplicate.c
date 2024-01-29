#include "minishell.h"

t_env	*ft_envlist_duplicate(t_env **envlist)
{
	t_env	*list;
	t_env	*new;
	t_env	*copy;

	list = *envlist;
	copy = NULL;
	if (*envlist == NULL)
		return (NULL);
	while (list != NULL)
	{
		new = ft_duplicate_node(list->name, list->value);
		if (copy == NULL)
			copy = new;
		else
			ft_add_to_list(&copy, new);
		list = list->next;
	}
	return copy;
}

t_env	*ft_duplicate_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node)
	{
		new_node->name = ft_strdup(name);
		new_node->value = ft_strdup(value);
		new_node->next = NULL;
		return (new_node);
	}
	return (NULL);
}

char **ft_env_duplicate(char **envp)
{
	int i;
    char **copy;
    
	i = 0;
    while (envp[i])
		i++;
    copy = (char **)malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return NULL;
    i = 0;
    while (envp[i])
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (i > 0)
            {
                free(copy[i - 1]);
                i--;
            }
            free(copy);
            return NULL;
        }
        i++;
    }
    copy[i] = NULL;
    return copy;
}