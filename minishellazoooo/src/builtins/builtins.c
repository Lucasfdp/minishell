#include "builtins.h"

void	execute_builtins(char *input, t_shell *shell)
{
	char	**args;

	args = ft_split(input, ' ');
	if (ft_strncmp(args[0], "echo", 5) == 0)
		execute_echo(args);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(args[0], "env", 4) == 0)
		execute_env(shell->env);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		execute_export(args, &shell->env);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		execute_unset(args, &shell->env);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		execute_cd(args, &shell->env);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		execute_exit(args, shell);
}