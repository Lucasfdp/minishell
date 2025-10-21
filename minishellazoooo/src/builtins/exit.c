#include "builtins.h"

void	check_digit(char **args, t_shell *shell)
{
	int		i;

	i = 0;
	if (args[1][0] == '-' || args[1][0] == '+')
		i++;
	if (!args[1][i])
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args[1]);
		shell->exit_status = 255;
		exit(255);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				args[1]);
			shell->exit_status = 255;
			exit(255);
		}
		i++;
	}
}

void	execute_exit(char **args, t_shell *shell)
{
	if (!args[1])
		exit(shell->exit_status);
	else if (args[1] && args[2])
	{
		ft_fprintf(STDERR_FILENO, "exit\nexit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	else if (args[1])
	{
		check_digit(args, shell);
		shell->exit_status = ft_atoi(args[1]) % 256;
		free_shell(shell);
		exit(shell->exit_status);
	}
}
