#include "minishell.h"

t_env	*ft_create_node_for_envList(char *var_array)
{
	t_env	*new_node;
	int		i;

	i = 0;
	new_node = malloc(sizeof(t_env));
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

// t_command *ft_init_node_for_command(command)
// { 
//     command->argCount = 0;
//     command->name = NULL;
//     command->args = NULL;
//     command->redirectFile = NULL;
//     command->next = NULL;
//     command->prev = NULL;
//     command->tokenType = NOT;
//     command->quoteType = NORMAL;
    
//     return new_node_command;
// }

// t_command *ft_init_new_command(char *name) 
// {
//     t_command *newCommand;
    
//     newCommand = (t_command *)malloc(sizeof(t_command));
    
//     if (newCommand == NULL) 
//     {
//         perror("Memory allocation failed in ft_init_new_command");
//         exit(EXIT_FAILURE);
//     }

//     // Initialisation des champs de la structure
//     newCommand->name = strdup(name);
//     newCommand->data = NULL; // À ajuster en fonction de l'utilisation prévue de `data`
//     newCommand->args = NULL;
//     newCommand->argCount = 0;
//     newCommand->redirectFile = NULL;
//     newCommand->fd[0] = newCommand->fd[1] = -1;
//     newCommand->next = NULL;
//     newCommand->prev = NULL;
//     newCommand->tokenType = COMMAND_TYPE; // Assurez-vous d'ajuster cela si nécessaire
//     newCommand->quoteType = NORMAL;/* Assurez-vous d'ajuster cela en fonction de votre logique */

//     return newCommand;
// }

void ft_init_new_node(t_commandList *commandList, t_command *command, char *token)
{
    command->name = ft_strdup(token);
    command->data = NULL;
    command->args = (char **)malloc(sizeof(char *) * 2);
    if (command->args == NULL) 
    {
        perror("CHAOS, error allocating memory");
        ft_destroy_command(commandList);
        exit(EXIT_FAILURE);
    }
    command->args[0] = ft_strdup(token);
    command->args[1] = NULL;
    command->argCount = 1;
    command->redirectFile = NULL;
    command->fd[0] = -1;
    command->fd[1] = -1;
    command->next = NULL;
    command->prev = NULL;
    command->tokenType = ft_allocate_token_type(token);
    command->quoteType = ft_check_and_allocate_quote_type(token);
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

/*
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
*/