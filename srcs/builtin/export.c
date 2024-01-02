#include "minishell.h"

int	check_args(char *name)
{
	if (!ft_check_wrong_char(name))
		return (0);
	if (!ft_is_only_digit(name))
		return (0);
	return (1);
}

int	ft_error_export(char *command, char *arg, char *message, int status)
{
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	return (status);
}

int	ft_check_wrong_char(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (0);
	while (str[i])
	{
		if (ft_is_sep(str[i]) || (str[i] >= 33 && str[i] <= 47)
			|| (str[i] == '=' && str[i + 1] == '='))
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_env **envlist, t_command *cmd)
{
	if (cmd->name != NULL && cmd->args != NULL && cmd->args[0] != NULL)
	{
		if (!check_args(cmd->args[0]))
			return (ft_error_export("export: ", cmd->args[0],
					": not a valid identifier", 1));
		if (!ft_add_var_to_list(envlist, cmd->args[0]))
			return (-1);
	}
	else
		ft_print_export_list(envlist);
	return (1);
}
