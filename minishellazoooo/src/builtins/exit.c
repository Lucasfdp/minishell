#include "builtins.h"

void	execute_exit(char **args, t_shell *shell)
{
	int		i;

	i = 0;
	if (!args[1])
	{
		printf("exit");
		exit(shell->last_status);
	}
	else if (args[1] && args[2])
	{
		printf("exit: too many arguments");
		shell->last_status = 1;
	}
	else if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				printf("exit: numeric argument required");
				shell->last_status = 2;
				exit(2);
			}
			i++;
		}
		printf("exit");
		shell->last_status = ft_atoi(args[1]) % 256;
		exit(shell->last_status);
	}
}