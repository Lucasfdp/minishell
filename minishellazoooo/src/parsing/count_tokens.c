#include "parsing.h"

int	skip_whitespace(char *input, int i)
{
	while (ft_isspace(input[i]))
		i++;
	return (i);
}

static int	count_operator(char *input, int i, int *count)
{
	(*count)++;
	if ((input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>'))
		return (i + 2);
	return (i + 1);
}

static void	toggle_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (c == '"' && !(*in_single))
		*in_double = !(*in_double);
}

static int	count_word_token(char *input, int i)
{
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	while (input[i] && (!ft_isspace(input[i]) || in_single || in_double))
	{
		toggle_quotes(input[i], &in_single, &in_double);
		if (!in_single && !in_double && is_operator_char(input[i]))
			break ;
		i++;
	}
	return (i);
}

int	count_tokens(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_operator_char(input[i]))
		{
			i = count_operator(input, i, &count);
			continue ;
		}
		count++;
		i = count_word_token(input, i);
	}
	return (count);
}
