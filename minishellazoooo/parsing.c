#include "minishell.h"

int	count_tokens(char *input)
{
	int	i;
	int	num_tokens;

	i = 0;
	num_tokens = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			num_tokens++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
		}
		else
			i++;
	}
	return (num_tokens);
}

int	tokeniser(char *input)
{
	char	**tokens;
	int		num_tokens;
	int i = 0;

	num_tokens = count_tokens(input);
	tokens = (char **)malloc(sizeof(char *) * num_tokens);
	if (!tokens)
		return (0);
	tokens = ft_split((const char *)input, ' ');
	while (tokens[i])
		printf("%s\n", tokens[i]);
	return (1);
}