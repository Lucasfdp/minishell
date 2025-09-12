#include "builtins.h"

void	execute_unset(char **args, char ***env)
{
	int	i;
	int	j;
	char	*var;

	i = 1;
	while (args[i])
	{
		j = 0;
		var = ft_strjoin_gnl(args[i], "=");
		while ((*env)[j])
		{
			if (ft_strncmp(var, (*env)[j], ft_int_strlen(var)) == 0)
			{
				free((*env)[j]);
				while ((*env)[j + 1])
				{
					(*env)[j] = (*env)[j + 1];
					j++;
				}
				(*env)[j] = NULL;
				break ;
			}
			else
				j++;
		}
		free(var);
		i++;
	}
}
