/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_more.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 05:57:32 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/25 05:57:33 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_parse_step(int step, t_shell *shell, t_command **command)
{
	if (step == -1)
		return (0);
	if (step == 0)
	{
		do_error_stuff(shell, "|", command);
		return (0);
	}
	if (g_sigint_received)
	{
		free_command(*command);
		return (0);
	}
	return (1);
}

void	parse_tokens_loop(t_shell *shell, char **tokens,
			t_command **command, t_parse_state *ps)
{
	int	i;
	int	step;

	i = 0;
	while (tokens[i])
	{
		step = process_token(tokens, i, shell, ps);
		if (!handle_parse_step(step, shell, command))
			return ;
		i += step;
	}
}
