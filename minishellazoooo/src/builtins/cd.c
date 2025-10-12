/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:34:34 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/10 10:33:46 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


char	*get_home(char **env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_old_pwd(char **env)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
		return (env[i] + 7);
		i++;
	}
	return (NULL);
}

void	execute_cd(char **args, char ***env)
{
	char	*home;
	char	*old_pwd;
	char	*cwd;

	home = get_home(*env);
	old_pwd = get_old_pwd(*env);
	cwd = getcwd(NULL, 0);
	if (!args[1])
	{
		if (chdir(home) != 0)
			ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
		set_env_var(env, ft_strjoin("OLDPWD=", cwd));
	}
	else if (args[2])
		printf("cd: Too many arguments\n");
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		if (chdir(old_pwd) != 0)
			printf("cd: OLD_PWD not set\n");
		else
		{	
			printf("%s\n", old_pwd);
			set_env_var(env, ft_strjoin("OLDPWD=", cwd));
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
			ft_fprintf(STDERR_FILENO, "bash: line 0: cd: %s: No such file or directory\n", args[1]);
		set_env_var(env, ft_strjoin("OLDPWD=", cwd));
	}
}
