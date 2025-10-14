#include "builtins.h"

char	*extract_key(char *var)
{
	int		i;
	char	*key;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = (char *)malloc(i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		key[i] = var[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	**append_to_env(char **env, char *new_var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = -1;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	while (++j < i)
		new_env[j] = env[j];
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

void	set_env_var(char ***env, char *new_var)
{
	int		idx;
	char	*key;

	key = extract_key(new_var);
	if (!key)
		return ;
	idx = find_env_index(*env, key);
	if (idx >= 0)
	{
		free((*env)[idx]);
		(*env)[idx] = ft_strdup(new_var);
	}
	else
		*env = append_to_env(*env, new_var);
	free(key);
}

void	print_export(char **env)
{
	int		i;
	char	*equal_sign;
	char	**sorted_env;

	i = 0;
	sorted_env = order_env(env);
	while (sorted_env[i])
	{
		printf("declare -x ");
		equal_sign = ft_strchr(sorted_env[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			printf("%s=\"%s\"\n", sorted_env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
			printf("%s\n", sorted_env[i]);
		i++;
	}
	free_array(sorted_env);
}

void	execute_export(char **args, char ***env)
{
	int	i;

	if (!args[1])
	{
		print_export(*env);
		return ;
	}
	i = 1;
	while (args[i])
	{
		set_env_var(env, args[i]);
		i++;
	}
}
