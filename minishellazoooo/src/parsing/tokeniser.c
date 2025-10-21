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
	int	starts_with_single;
	int	starts_with_double;

	starts_with_single = (input[i] == '\'');
	starts_with_double = (input[i] == '"');
	i = extract_word_to_buf(input, i, ts->buf, &ts->qs);
	create_token_from_buf(ts->buf, ts->tokens, *(ts->index),
		starts_with_single, starts_with_double);
	(*(ts->index))++;
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
			i = handle_operator(input, i, ts->tokens, (*(ts->index))++);
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
