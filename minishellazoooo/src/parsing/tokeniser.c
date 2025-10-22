/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:54:49 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/22 01:35:03 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_quotes_and_counters(t_quote_state *qs, int *i, int *j)
{
	(*i) = 0;
	(*j) = 0;
	qs->single_q = 0;
	qs->double_q = 0;
}

static void	init_tokenizer(t_tok_state *ts, t_token ***tokens, char *input)
{
	char	*buf;

	buf = alloc_tokeniser_resources(tokens, input);
	ts->tokens = *tokens;
	ts->index = malloc(sizeof(int));
	*(ts->index) = 0;
	ts->buf = buf;
	ts->qs.single_q = 0;
	ts->qs.double_q = 0;
}

static int	handle_word(char *input, int i, t_tok_state *ts)
{
	t_quote_flags	qf;
	int				result;

	qf.in_single = (input[i] == '\'');
	qf.in_double = (input[i] == '"');
	result = extract_word_to_buf(input, i, ts->buf, &ts->qs);
	if (result < 0)
	{
		qf.in_single = 1;
		qf.in_double = 0;
		result = -result;
	}
	i = result;
	create_token_from_buf(ts->buf, ts, &qf);
	return (i);
}

static int	process_tokens(char *input, t_tok_state *ts)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_operator_char(input[i]) && !ts->qs.single_q && !ts->qs.double_q)
			i = handle_operator(input, i, ts);
		else
			i = handle_word(input, i, ts);
	}
	return (*(ts->index));
}

t_token	**tokeniser(char *input)
{
	int				i;
	t_token			**tokens;
	t_tok_state		ts;

	init_tokenizer(&ts, &tokens, input);
	if (!ts.buf)
		return (NULL);
	i = process_tokens(input, &ts);
	tokens[i] = NULL;
	free(ts.buf);
	free(ts.index);
	if (has_unclosed_quotes(&ts.qs))
		return (NULL);
	return (tokens);
}
