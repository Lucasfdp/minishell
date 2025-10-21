/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:58:17 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:58:18 by luferna3         ###   ########.fr       */
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

void	execute_echo(char **args)
{
	char	*output;
	int		i;

	i = 0;
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(args[1], "-n", 3) == 0)
	{
		i = 1;
		output = join_args(args, &i);
		ft_fprintf(STDOUT_FILENO, "%s", output);
	}
	else
	{
		output = join_args(args, &i);
		ft_fprintf(STDOUT_FILENO, "%s\n", output);
	}
	free(output);
}
