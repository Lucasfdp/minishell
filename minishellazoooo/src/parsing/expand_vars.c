/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:55:28 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/24 05:31:34 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*strjoin_free(char *str, char *to_add)
{
	char	*tmp;

	tmp = ft_strjoin(str, to_add);
	free(str);
	return (tmp);
}

void	expand_tokens(t_shell *shell, t_token **tokens)
{
	int		i;
	char	*expanded;

	i = 0;
	while (tokens[i])
	{
		if (!tokens[i]->in_single)
		{
			expanded = expand_variables(shell, tokens[i]->value,
					tokens[i]->in_double);
			free(tokens[i]->value);
			tokens[i]->value = expanded;
		}
		i++;
	}
}

bool	validate_tokens(char **tokens, const char *cmdline)
{
	int					i;
	t_validate_ctx		ctx;

	ctx.tokens = tokens;
	ctx.cmdline = cmdline;
	ctx.prev = TOKEN_NONE;
	i = 0;
	while (tokens[i])
	{
		ctx.curr = get_token_type(tokens[i]);
		if (!validate_current_token(&ctx, i))
			return (false);
		ctx.prev = ctx.curr;
		i++;
	}
	if (ctx.prev == TOKEN_PIPE)
	{
		syntax_error_unexpected_token(NULL, cmdline);
		return (false);
	}
	return (true);
}

void	init_parse_state(t_parse_state *ps, t_command **cmd, t_token_type *prev)
{
	*cmd = init_command();
	*prev = TOKEN_NONE;
	ps->cmd = cmd;
	ps->prev = prev;
}

void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_array(cmd->args);
	if (cmd->redirs)
		free_redirs(cmd->redirs);
	free(cmd);
}
