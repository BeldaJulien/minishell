#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void initialization_of_errors(t_mini *shell)
{
    if (shell != NULL) {
        shell->error = malloc(sizeof(t_error));
        if (shell->error != NULL) {
            shell->error->error = FALSE;
            shell->error->error_name = NULL;
            shell->error->next = NULL;
            shell->error->prev = NULL;
        }
    }
}
