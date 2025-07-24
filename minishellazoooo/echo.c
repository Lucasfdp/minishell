#include "minishell.h"

void	execute_echo(char **args)
{
	char	*output;
	int		i;

	output = ft_strdup("");
	i = 0;
	while(args[++i])
	{
		output = ft_strjoin_gnl(output, args[i]);
		output = ft_strjoin_gnl(output, " ");
	}
	printf("%s\n",output);
}