/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:58:05 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/22 02:05:52 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

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

static void	execute_builtins2(t_command *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		execute_echo(cmd->args);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		execute_pwd();
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		execute_env(shell->env);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		execute_export(cmd->args, &shell->env);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		execute_unset(cmd->args, &shell->env);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		execute_cd(shell, cmd->args, &shell->env);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		execute_exit(cmd->args, shell);
}

void	execute_builtins(t_command *cmd, t_shell *shell)
{
	if (cmd->input_fd != STDIN_FILENO)
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			error_exit("dup2 input", 1);
	if (cmd->output_fd != STDOUT_FILENO)
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			error_exit("dup2 output", 1);
	execute_builtins2(cmd, shell);
}
