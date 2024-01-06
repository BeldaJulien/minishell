#include "minishell.h" 

void ft_split_string_export_argument(const char *arg, char **name, char **value) 
{
    char *equals;
	
	equals = ft_strchr(arg, '=');

    if (equals != NULL) 
	{
        *equals = '\0'; // Sépare la chaîne en deux au niveau du signe '='
        *name = ft_strdup(arg); // La partie avant le '=' est le nom de la variable
        *value = ft_strdup(equals + 1); // La partie après le '=' est la valeur de la variable
    } else 
	{
        *name = NULL;
        *value = NULL;
    }
}

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