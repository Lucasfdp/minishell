/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:55:17 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:55:18 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_pipe(t_shell *shell, t_command **cmd)
{
	if (!(*cmd)->args && !(*cmd)->redirs)
		return (0);
	add_command(shell, *cmd);
	*cmd = init_command();
	if (!(*cmd))
		return (-1);
	return (1);
}

static int	handle_redir(char **tokens, int i, t_command *cmd, t_shell *shell)
{
	int				type;
	int				should_expand;
	t_redir_params	params;

	type = is_redir(tokens[i]);
	if (!validate_next_redir_token(tokens, i))
	{
		do_error_stuff(shell, tokens[i + 1], &cmd);
		return (-1);
	}
	should_expand = 1;
	if (type == REDIR_HEREDOC && shell->token_list && shell->token_list[i + 1])
	{
		should_expand = !(shell->token_list[i + 1]->in_single
				|| shell->token_list[i + 1]->in_double);
	}
	params.type = type;
	params.file_token = tokens[i + 1];
	params.should_expand = should_expand;
	add_redir(cmd, &params, shell);
	return (2);
}

static int	process_token(char **tokens, int i, t_shell *shell,
				t_parse_state *ps)
{
	int	type;
	int	result;

	if (ft_strcmp(tokens[i], "|") == 0)
	{
		result = handle_pipe(shell, ps->cmd);
		if (result <= 0)
			return (result);
		*(ps->prev) = TOKEN_PIPE;
		return (1);
	}
	type = is_redir(tokens[i]);
	if (is_redir_type(type))
	{
		result = handle_redir(tokens, i, *(ps->cmd), shell);
		return (result);
	}
	(*(ps->cmd))->args = add_arg((*(ps->cmd))->args, tokens[i]);
	*(ps->prev) = TOKEN_WORD;
	return (1);
}

static void	finalize_commands(t_shell *shell, t_command *cmd,
	t_token_type prev)
{
	if (prev == TOKEN_PIPE)
	{
		do_error_stuff(shell, NULL, &cmd);
		return ;
	}
	if (cmd->args || cmd->redirs)
		add_command(shell, cmd);
	else
		free(cmd);
}

void	fill_structs(t_shell *shell, char **tokens)
{
	int				i;
	int				step;
	t_command		*command;
	t_token_type	prev_type;
	t_parse_state	ps;

	init_parse_state(&ps, &command, &prev_type);
	if (!command)
		return ;
	i = 0;
	while (tokens[i])
	{
		step = process_token(tokens, i, shell, &ps);
		if (step == -1)
			return ;
		if (step == 0)
		{
			do_error_stuff(shell, "|", &command);
			return ;
		}
		i += step;
	}
	finalize_commands(shell, command, prev_type);
}
