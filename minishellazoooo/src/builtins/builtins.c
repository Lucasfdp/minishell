#include "builtins.h"

void	execute_builtins(t_command *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		execute_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		execute_env(shell->env);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		execute_export(cmd->args, &shell->env);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		execute_unset(cmd->args, &shell->env);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		execute_cd(cmd->args, &shell->env);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		execute_exit(cmd->args, shell);
}
