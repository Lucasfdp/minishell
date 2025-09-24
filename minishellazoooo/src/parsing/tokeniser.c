#include "minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	count_tokens(char *input)
{
	int i = 0;
	int count = 0;
	int in_single = 0;
	int in_double = 0;

	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break;
		if (is_operator_char(input[i]))
		{
			count++;
			if ((input[i] == '<' && input[i + 1] == '<') ||
				(input[i] == '>' && input[i + 1] == '>'))
				i += 2;
			else
				i++;
		}
		else
		{
			count++;
			while (input[i] && (!ft_isspace(input[i]) || in_single || in_double))
			{
				if (input[i] == '\'' && !in_double)
					in_single = !in_single;
				else if (input[i] == '\"' && !in_single)
					in_double = !in_double;
				else if (!in_single && !in_double && is_operator_char(input[i]))
					break;
				i++;
			}
		}
	}
	return (count);
}

char	**tokeniser(char *input)
{
	char **tokens;
	char *command;
	int num_tokens = count_tokens(input);
	int single_q = 0;
	int	double_q = 0;
	int i = 0;
	int j = 0;
	int	k = 0;
	char op[2];


	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (!tokens)
		return NULL;
	command = malloc(ft_int_strlen(input) + 1);
	if (!command)
		return NULL;
	while (input[i])
	{
		if (input[i] == '\'' && !double_q)
		{
			single_q = !single_q;
			i++;
			continue;
		}
		if (input[i] == '"' && !single_q)
		{
			double_q = !double_q;
			i++;
			continue; 
		}
		if ((input[i] == '|' || input[i] == '<' || input[i] == '>') && !single_q && !double_q)
		{
			if (k > 0)
			{
				command[k] = '\0';
				tokens[j++] = ft_strdup(command);
				k = 0;
			}
			if (input[i] == '<' && input[i+1] == '<')
			{
				tokens[j++] = ft_strdup("<<");
				i += 2;
				continue;
			}
			if (input[i] == '>' && input[i+1] == '>')
			{
				tokens[j++] = ft_strdup(">>");
				i += 2;
				continue;
			}
			op[0] = input[i];
			op[1] = '\0';
			tokens[j++] = ft_strdup(op);
			i++;
			continue;
		}
		if (ft_isspace(input[i]) && !single_q && !double_q)
		{
			if (k > 0) {
				command[k] = '\0';
				tokens[j++] = ft_strdup(command);
				k = 0;
			}
			i++;
			continue;
		}
		command[k++] = input[i++];
	}
	if (k > 0)
	{
		command[k] = '\0';
		tokens[j++] = ft_strdup(command);
	}
	tokens[j] = NULL;
	if (single_q || double_q) 
	{
		// report syntax error, free tokens
		return (NULL);
	}

	free(command);
	return tokens;
}
