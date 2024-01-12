#include "minishell.h"

t_env	*ft_create_node_for_args(char *var_array)
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

t_command *ft_create_node_for_command(void)
{
    t_command *new_node_command;
    
    new_node_command = (t_command *)malloc(sizeof(t_command));
    
    if (new_node_command == NULL) {
        fprintf(stderr, "Chaos, memory allocation failed with new_node_command\n");
        exit(EXIT_FAILURE);
    }    
    new_node_command->argCount = 0;
    new_node_command->name = NULL;
    new_node_command->args = NULL;
    new_node_command->redirectFile = NULL;
    new_node_command->next = NULL;
    new_node_command->prev = NULL;
    new_node_command->tokenType = NOT;
    new_node_command->quoteType = NORMAL;
    
    return new_node_command;
}

t_env *ft_create_node_for_export_argument(char *name, char *value)
{
    t_env *new_node;
    
    new_node = malloc(sizeof(t_env));
    if (new_node == NULL) 
    {
        perror("Memory allocation error in ft_create_node_export_argument\n");
        exit(EXIT_FAILURE);
    }

    new_node->name = ft_strdup(name);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    
    
    return new_node;
}

t_env *ft_create_node_for_envVar(t_command *cmd)
{
    t_env *new_node = malloc(sizeof(t_env));
    if (new_node == NULL) 
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    new_node->name = ft_strdup(cmd->name);
    new_node->value = ft_strdup((char *)cmd->data);
    new_node->next = NULL;
    
    return new_node;
}

void *ft_create_node_by_type(void *node, t_node_type type, t_command *command) 
{
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    if (type == ENV_NODE) {
        ft_create_node_for_envVar(command);
    } else if (type == COMMAND_NODE) {
        ft_create_node_for_command();
    }
    return NULL;
} 
