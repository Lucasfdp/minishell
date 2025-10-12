#include "builtins.h"

void	execute_echo(char **args)
{
	char	*output;
	int		i;

	output = ft_strdup("");
	i = 0;
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(args[1], "-n", 3) == 0)
	{
		i = 1;
		while (args[++i])
		{
			output = ft_strjoin_gnl(output, args[i]);
			if (args[i + 1])
				output = ft_strjoin_gnl(output, " ");
		}
		ft_fprintf(STDOUT_FILENO, "%s", output);
	}
	else
	{	
		while(args[++i])
		{
			output = ft_strjoin_gnl(output, args[i]);
			if (args[i + 1])
				output = ft_strjoin_gnl(output, " ");
		}
		ft_fprintf(STDOUT_FILENO, "%s\n",output);
	}
}
