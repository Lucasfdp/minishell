#include "executor.h"

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*try_paths(char **split_paths, char *cmd)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (split_paths[i])
	{
		tmp = ft_strjoin(split_paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_shell *shell, t_command *cmd)
{
	char	**split_paths;
	char	*path;
	char	*result;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (ft_strdup(cmd->args[0]));
		return (NULL);
	}
	path = get_path_from_env(shell->env);
	if (!path)
		return (NULL);
	split_paths = ft_split(path, ':');
	if (!split_paths)
		return (NULL);
	result = try_paths(split_paths, cmd->args[0]);
	free_array(split_paths);
	return (result);
}

int	ft_lstsize_2(t_command *lst)
{
	int			count;
	t_command	*temp;

	count = 0;
	temp = lst;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	detect_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}
