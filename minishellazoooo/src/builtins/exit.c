#include "builtins.h"

void	check_digit(char **args, t_shell *shell)
{
	int		i;

	i = 0;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_fprintf(STDERR_FILENO, "exit: numeric argument required\n");
			shell->exit_status = 2;
			exit(2);
		}
		i++;
	}
}

void	execute_exit(char **args, t_shell *shell)
{
	if (!args[1])
	{
		ft_fprintf(STDERR_FILENO, "exit\n");
		exit(shell->exit_status);
	}
	else if (args[1] && args[2])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		free(shell->input);
		shell->exit_status = 1;
	}
	else if (args[1])
	{
		check_digit(args, shell);
		shell->exit_status = ft_atoi(args[1]) % 256;
		free_shell(shell);
		exit(shell->exit_status);
	}
}

// potentially change prints