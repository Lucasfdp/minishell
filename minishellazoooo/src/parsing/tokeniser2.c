#include "parsing.h"

int	handle_operator(char *input, int i, t_token **tokens, int j)
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
	tokens[j] = malloc(sizeof(t_token));
	tokens[j]->value = ft_strdup(op);
	tokens[j]->in_single = 0;
	tokens[j]->in_double = 0;
	return (i);
}

int	process_backslash(char *input, int i, char *buf, int *k, int dq)
{
	i++;
	if (input[i])
	{
		if (!dq || input[i] == '$' || input[i] == '"'
			|| input[i] == '\\' || input[i] == '`')
			buf[(*k)++] = input[i];
		else
			buf[(*k)++] = '\\';
		i++;
	}
	return (i);
}

int	process_word_char(char *in, int i, char *buf, int *k, t_quote_state *qs)
{
	if (in[i] == '\\')
		return (process_backslash(in, i, buf, k, qs->double_q));
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
	buf[(*k)++] = in[i];
	return (i + 1);
}

int	extract_word_to_buf(char *in, int i, char *buf, t_quote_state *qs)
{
	int	k;

	k = 0;
	while (in[i] && (!ft_isspace(in[i]) || qs->single_q || qs->double_q))
	{
		i = process_word_char(in, i, buf, &k, qs);
		if (!qs->single_q && !qs->double_q && is_operator_char(in[i]))
			break ;
	}
	buf[k] = '\0';
	return (i);
}

void	create_token_from_buf(char *buf, t_token **tokens, int j, int ss, int sd)
{
	tokens[j] = malloc(sizeof(t_token));
	tokens[j]->value = ft_strdup(buf);
	tokens[j]->in_single = ss;
	tokens[j]->in_double = sd;
}
