/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:58:17 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/22 00:20:35 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*join_args(char **args, int *i)
{
	char	*output;
	char	*tmp;

	output = ft_strdup("");
	while (args[++(*i)])
	{
		tmp = ft_strjoin_gnl(output, args[(*i)]);
		output = tmp;
		if (args[(*i) + 1])
		{
			tmp = ft_strjoin_gnl(output, " ");
			output = tmp;
		}
	}
	return (output);
}

// void	execute_echo(char **args)
// {
// 	char	*output;
// 	int		i;
// 	int		j;
// 	int		args_count;

// 	i = 0;
// 	j = 2;
// 	args_count = count_matrix(args);
// 	if (!args[1])
// 	{
// 		printf("\n");
// 		return ;
// 	}
// 	if (ft_strncmp(args[1], "-n", 3) == 0)
// 	{
// 		while (j < args_count)
// 		{
// 			if (ft_strncmp(args[j], "-n", 3) == 0)
// 				j++;
// 		}
// 		i = 1;
// 		output = join_args(args, &i);
// 		ft_fprintf(STDOUT_FILENO, "%s", output);
// 	}
// 	else
// 	{
// 		output = join_args(args, &i);
// 		ft_fprintf(STDOUT_FILENO, "%s\n", output);
// 	}
// 	free(output);
// }

// Helper: Check if all args starting at index are -n flags
static int	skip_n_flags(char **args, int start)
{
	int	i;

	i = start;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
		i++;
	return (i);
}

// Helper: Print echo output
static void	print_echo(char *output, int newline)
{
	if (newline)
		ft_fprintf(STDOUT_FILENO, "%s\n", output);
	else
		ft_fprintf(STDOUT_FILENO, "%s", output);
}

void	execute_echo(char **args)
{
	char	*output;
	int		i;
	int		newline;

	if (!args[1])
	{
		printf("\n");
		return ;
	}
	newline = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		i = skip_n_flags(args, 1) - 1;
		newline = 0;
	}
	else
		i = 0;
	output = join_args(args, &i);
	print_echo(output, newline);
	free(output);
}
