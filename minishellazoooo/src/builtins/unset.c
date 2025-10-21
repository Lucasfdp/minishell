#include "builtins.h"

void	unset_single(char ***env, char *var)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, len) == 0
			&& ((*env)[i][len] == '=' || (*env)[i][len] == '\0'))
		{
			free((*env)[i]);
			j = i;
			while ((*env)[j + 1])
			{
				(*env)[j] = (*env)[j + 1];
				j++;
			}
			(*env)[j] = NULL;
			return ;
		}
		i++;
	}
}

void	execute_unset(char **args, char ***env)
{
	int		i;

	i = 1;
	while (args[i])
	{
		unset_single(env, args[i]);
		i++;
	}
}
