#include "builtins.h"

void	execute_env(char **envp_shell)
{
	int	i;

	i = -1;
	while (envp_shell[++i])
		printf("%s\n", envp_shell[i]);
}

int	find_env_index(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_int_strlen(key);
	if (!env || !key)
		return (-1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len))
		{
			if (env[i][len] == '=' || env[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**order_env(char **env)
{
	char	**sorted_env;
	char	*temp;
	int		i;
	int		env_len;

	sorted_env = copy_matrix(env);
	env_len = count_matrix(sorted_env);
	i = 0;
	while (i < env_len - 1)
	{
		if (ft_strcmp(sorted_env[i], sorted_env[i + 1]) > 0)
		{
			temp = sorted_env[i];
			sorted_env[i] = sorted_env[i + 1];
			sorted_env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	return (sorted_env);
}
