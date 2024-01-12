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
