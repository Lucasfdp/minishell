/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:58:22 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/28 16:24:59 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// void	check_digit(char **args, t_shell *shell)
// {
// 	int		i;

// 	i = 0;
// 	if (args[1][0] == '-' || args[1][0] == '+')
// 		i++;
// 	if (!args[1][i])
// 	{
// 		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
// 			args[1]);
// 		shell->exit_status = 255;
// 		exit(255);
// 	}
// 	while (args[1][i])
// 	{
// 		if (!ft_isdigit(args[1][i]))
// 		{
// 			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
// 				args[1]);
// 			shell->exit_status = 255;
// 			exit(255);
// 		}
// 		i++;
// 	}
// }

// void	execute_exit(char **args, t_shell *shell)
// {
// 	if (!args[1])
// 	{
// 		free_shell(shell);
// 		exit(shell->exit_status);
// 	}
// 	else if (args[1] && args[2])
// 	{
// 		ft_fprintf(STDERR_FILENO, "exit\nexit: too many arguments\n");
// 		shell->exit_status = 1;
// 		return ;
// 	}
// 	else if (args[1])
// 	{
// 		check_digit(args, shell);
// 		shell->exit_status = ft_atoi(args[1]) % 256;
// 		free_shell(shell);
// 		exit(shell->exit_status);
// 	}
// }

static int	is_numeric_overflow(char *str)
{
	int		i;
	int		len;
	char	*max_long;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	len = 0;
	while (str[i + len])
		len++;
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	max_long = "9223372036854775807";
	if (str[0] == '-')
		max_long = "9223372036854775808";
	while (str[i])
	{
		if (str[i] > max_long[i - (str[0] == '-' || str[0] == '+')])
			return (1);
		i++;
	}
	return (0);
}

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
		free_shell(shell);
		exit(255);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
				args[1]);
			free_shell(shell);
			exit(255);
		}
		i++;
	}
	if (is_numeric_overflow(args[1]))
	{
		ft_fprintf(STDERR_FILENO, "exit: %s: numeric argument required\n",
			args[1]);
		free_shell(shell);
		exit(255);
	}
}

void	execute_exit(char **args, t_shell *shell)
{
	if (!args[1])
	{
		free_shell(shell);
		exit(shell->exit_status);
	}
	else if (args[2])
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		shell->exit_status = 1;
		return ;
	}
	check_digit(args, shell);
	shell->exit_status = ft_atoi(args[1]) % 256;
	free_shell(shell);
	exit(shell->exit_status);
}
