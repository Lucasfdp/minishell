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
	while (env[i])
	{
		if (env[i][len] == '=' && (!ft_strncmp(env[i], key, len)))
			return (i);
		i++;
	}
	return (-1);
}

// potentially change _var name from minishellazooo to env