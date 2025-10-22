/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:54:42 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/22 02:20:08 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_operator(char *input, int i, t_tok_state *ts)
{
	char	op[3];

	if (input[i] == '<' && input[i + 1] == '<')
	{
		ft_strlcpy(op, "<<", 3);
		i += 2;
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		ft_strlcpy(op, ">>", 3);
		i += 2;
	}
	else
	{
		op[0] = input[i++];
		op[1] = '\0';
	}
	ts->tokens[*(ts->index)] = malloc(sizeof(t_token));
	ts->tokens[*(ts->index)]->value = ft_strdup(op);
	ts->tokens[*(ts->index)]->in_single = 0;
	ts->tokens[*(ts->index)]->in_double = 0;
	(*(ts->index))++;
	return (i);
}

int	process_backslash(char *input, int i, t_buf_state *bs, int dq)
{
	i++;
	if (input[i])
	{
		if (!dq || input[i] == '$' || input[i] == '"'
			|| input[i] == '\\' || input[i] == '`')
			bs->buf[(*(bs->k))++] = input[i];
		else
			bs->buf[(*(bs->k))++] = '\\';
		i++;
	}
	return (i);
}

int	process_word_char(char *in, int i, t_buf_state *bs, t_quote_state *qs)
{
	if (in[i] == '\\')
		return (process_backslash(in, i, bs, qs->double_q));
	else if (in[i] == '\'' && !qs->double_q)
	{
		qs->single_q = !qs->single_q;
		return (i + 1);
	}
	else if (in[i] == '"' && !qs->single_q)
	{
		qs->double_q = !qs->double_q;
		return (i + 1);
	}
	else if (!qs->single_q && !qs->double_q && is_operator_char(in[i]))
		return (i);
	bs->buf[(*(bs->k))++] = in[i];
	return (i + 1);
}

int	extract_word_to_buf(char *in, int i, char *buf, t_quote_state *qs)
{
	int				k;
	t_buf_state		bs;
	int				had_single_content;

	k = 0;
	bs.buf = buf;
	bs.k = &k;
	had_single_content = 0;
	while (in[i] && (!ft_isspace(in[i]) || qs->single_q || qs->double_q))
	{
		if (qs->single_q && in[i] != '\'')
			had_single_content = 1;
		i = process_word_char(in, i, &bs, qs);
		if (!qs->single_q && !qs->double_q && is_operator_char(in[i]))
			break ;
	}
	buf[k] = '\0';
	if (had_single_content)
		return (-i);
	return (i);
}

void	create_token_from_buf(char *buf, t_tok_state *ts, t_quote_flags *qf)
{
	ts->tokens[*(ts->index)] = malloc(sizeof(t_token));
	ts->tokens[*(ts->index)]->value = ft_strdup(buf);
	ts->tokens[*(ts->index)]->in_single = qf->in_single;
	ts->tokens[*(ts->index)]->in_double = qf->in_double;
	(*(ts->index))++;
}
