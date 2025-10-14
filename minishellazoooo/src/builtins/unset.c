#include "builtins.h"

void	unset_single(char ****env, char *var)
{
	int	j;

	j = 0;
	while ((*env)[j])
	{
		if (ft_strncmp(var, (**env)[j], ft_int_strlen(var)) == 0)
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
}

void	execute_unset(char **args, char ***env)
{
	int		i;
	char	*var;

	i = 1;
	while (args[i])
	{
		var = ft_strjoin_gnl(args[i], "=");
		unset_single(&env, var);
		free(var);
		i++;
	}
}
