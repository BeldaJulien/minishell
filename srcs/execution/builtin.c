#include "minishell.h"

int	ft_is_builtin(t_command *cmd)
{
	if (!cmd->name)
	{
		ft_putstr_fd("command not found\n", 2);
		return (127);
	}
	if (ft_strcmp(cmd->name, "cd") == 0
		|| ft_strcmp(cmd->name, "echo") == 0
		|| ft_strcmp(cmd->name, "env") == 0
		|| ft_strcmp(cmd->name, "exit") == 0
		|| ft_strcmp(cmd->name, "export") == 0
		|| ft_strcmp(cmd->name, "pwd") == 0
		|| ft_strcmp(cmd->name, "unset") == 0)
		return (1);
	return (0);
}

int	ft_execute_builtin(t_command *cmd, t_env *envList)
{
	if (ft_strcmp(cmd->name, "cd") == 0)
		return (cd(cmd));
	if (ft_strcmp(cmd->name, "exit") == 0)
		return (ft_exit(cmd, envList));
	else if (ft_strcmp(cmd->name, "echo") == 0)
		return (echo(cmd->args, g_exit_code));
	else if (ft_strcmp(cmd->name, "env") == 0)
	{
		printf("Dans ft_execute_bulitin je vais print la envList\n");
		ft_display_envList(envList);
		return 0;
	}
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		return (pwd());
	else if (ft_strcmp(cmd->name, "unset") == 0)
		return (ft_unset(&envList, cmd));
	else if (ft_strcmp(cmd->name, "export") == 0)
		return (ft_export(&envList, cmd));
	fprintf(stderr, "Unknown builtin command: %s\n", cmd->name);
	return (-1);
}
