#include "minishell.h"

void ft_destroy_command(t_commandList *commandList)
{
	t_command	*current;
	t_command	*next;

	current = commandList->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	commandList->head = NULL;
	commandList->tail = NULL;
	commandList->length = 0;
}

void	ft_destroy_current_shell(t_mini *mini)
{
	if (mini->commands != NULL)
	{
		ft_destroy_command(mini->commands);
		free(mini->commands);
		mini->commands = NULL;
	}
	if (mini->av != NULL)
	{
		free(mini->av);
		mini->av = NULL;
	}
	if (mini->error != NULL)
	{
		free(mini->error);
		mini->error = NULL;
	}
	if (mini->exec != NULL)
	{
		free(mini->exec);
		mini->exec = NULL;
	}
}
