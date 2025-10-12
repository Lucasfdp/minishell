#include "builtins.h"

void	execute_exit(char **args, t_shell *shell)
{
	int		i;

	i = 0;
	if (!args[1])
	{
		ft_fprintf(STDERR_FILENO, "exit\n");
		exit(shell->exit_status);
	}
	else if (args[1] && args[2])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		shell->exit_status = 1;
	}
	else if (args[1])
	{
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
		//printf("exit\n");
		shell->exit_status = ft_atoi(args[1]) % 256;
		exit(shell->exit_status);
	}
}

// potentially change prints