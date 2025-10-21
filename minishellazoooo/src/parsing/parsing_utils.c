/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:55:13 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:55:14 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_type	get_token_type(char *token)
{
	if (!token)
		return (TOKEN_WORD);
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIR_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (TOKEN_HEREDOC);
	return (TOKEN_WORD);
}

void	syntax_error_unexpected_token(const char *token, const char *cmd)
{
	if (token)
		ft_fprintf(STDERR_FILENO,
			"bash: -c: line 0: syntax error near unexpected token `%s'\n",
			token);
	else
		ft_fprintf(STDERR_FILENO,
			"bash: -c: line 0: syntax error near unexpected token `newline'\n");
	if (cmd)
		ft_fprintf(STDERR_FILENO, "bash: -c: line 0: `%s'\n", cmd);
}

t_redir_type	is_redir(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (REDIR_HEREDOC);
	else
		return (REDIR_NONE);
}

void	copy_args(char **src, char **dest)
{
	int	i;

	if (!src || !dest)
		return ;
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
