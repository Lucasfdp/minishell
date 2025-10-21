/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:34:34 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 20:05:55 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

void	execute_return(t_shell *shell, char *old_pwd, char *cwd, char ****env)
{
	char	*new_cwd;
	
	if (!old_pwd)
	{
		ft_fprintf(STDERR_FILENO, "cd: OLDPWD not set\n");
		shell->exit_status = 1;
		return ;
	}
	if (chdir(old_pwd) != 0)
	{
		shell->exit_status = 1;
		perror("cd");
		return ;
	}
	printf("%s\n", old_pwd);
	set_env_var((*env), ft_strjoin("OLDPWD=", cwd));
	new_cwd = getcwd(NULL, 0);
	set_env_var((*env), ft_strjoin("PWD=", new_cwd));
	free(new_cwd);
	shell->exit_status = 0;
}

void	execute_norm(t_shell *shell, char **args, char *cwd, char ****env)
{
	char	*new_cwd;
	
	if (chdir(args[1]) != 0)
	{
		shell->exit_status = 1;
		ft_fprintf(STDERR_FILENO, "bash: line 0: cd: %s: No such file or directory\n",
			args[1]);
		return ;
	}
	set_env_var((*env), ft_strjoin("OLDPWD=", cwd));
	new_cwd = getcwd(NULL, 0);
	set_env_var((*env), ft_strjoin("PWD=", new_cwd));
	free(new_cwd);
	shell->exit_status = 0;
}

static void	cd_to_home(t_shell *shell, char *home, char *cwd, char ***env)
{
	char	*new_cwd;
	
	if (!home)
	{
		ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
		shell->exit_status = 1;
		return ;
	}
	if (chdir(home) != 0)
	{
		shell->exit_status = 1;
		perror("cd");
		return ;
	}
	set_env_var(env, ft_strjoin("OLDPWD=", cwd));
	new_cwd = getcwd(NULL, 0);
	set_env_var(env, ft_strjoin("PWD=", new_cwd));
	free(new_cwd);
	shell->exit_status = 0;
}

void	execute_cd(t_shell *shell, char **args, char ***env)
{
	char	*home;
	char	*old_pwd;
	char	*cwd;

	home = get_home(*env);
	old_pwd = get_old_pwd(*env);
	cwd = getcwd(NULL, 0);
	if (!args[1])
		cd_to_home(shell, home, cwd, env);
	else if (args[2])
	{
		ft_fprintf(STDERR_FILENO, "cd: too many arguments\n");
		shell->exit_status = 1;
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
		execute_return(shell, old_pwd, cwd, &env);
	else
		execute_norm(shell, args, cwd, &env);
	free(cwd);
}
