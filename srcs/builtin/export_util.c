#include "minishell.h" 

int ft_check_reserved_env_variables(const char *var_name)
{
	int i;
	i = 0;
    const char *reserved_variables[] = { "HOME", "PATH", "USER", "LOGNAME", "SHELL",
        "PWD", "OLDPWD", "PS1", "PS2", "PS3", "PS4", "IFS", "TERM", "EDITOR", 
        "VISUAL", "HISTSIZE", "HISTFILESIZE", "LANG", "TZ", NULL };
    
    while (reserved_variables[i] != NULL)
    {
        if (strcmp(var_name, reserved_variables[i]) == 0)
        {
            fprintf(stderr, "Reserved variable detected in ft_check_reserved_env\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return 0;
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