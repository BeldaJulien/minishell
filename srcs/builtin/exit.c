#include "minishell.h"

/* void	exit(t_command *command)
{
	int	exit_code;

	if (command->args[1] != NULL)
	{
		exit_code = ft_atoi(command->args[1]);
		if (exit_code == 0)
			exit(exit_code);
		else
		{
			if (dup2(STDOUT_FILENO, STDERR_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
			printf("Invalid exit code: %s\n", command->args[1]);
			exit(EXIT_FAILURE);
		}
	}
	else
		exit(0);
}
 */