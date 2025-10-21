/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:57:49 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:57:50 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_single_builtin(t_shell *shell)
{
	t_command	*cmd;

	if (shell->num_cmds != 1)
		return (0);
	cmd = shell->commands;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (!detect_builtin(cmd->args[0]))
		return (0);
	if (cmd->redirs)
		return (0);
	execute_builtins(cmd, shell);
	return (1);
}

static void	fork_and_exec(t_shell *shell, pid_t *pids)
{
	t_command	*cmd;
	int			i;

	cmd = shell->commands;
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			error_exit("fork", 1);
		if (pids[i] == 0)
			exec_child(shell, cmd);
		cmd = cmd->next;
		i++;
	}
}

static void	wait_all_children(t_shell *shell, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < shell->num_cmds)
	{
		waitpid(pids[i], &shell->exit_status, 0);
		i++;
	}
}

void	execute_commands(t_shell *shell)
{
	pid_t	*pids;

	shell->num_cmds = ft_lstsize_2(shell->commands);
	if (shell->num_cmds == 0)
		return ;
	if (handle_single_builtin(shell))
		return ;
	if (shell->num_cmds > 1)
		setup_pipes(shell);
	pids = (pid_t *)malloc(sizeof(pid_t) * shell->num_cmds);
	if (!pids)
		error_exit("malloc pids", 1);
	fork_and_exec(shell, pids);
	if (shell->num_cmds > 1)
		close_all_pipes(shell);
	wait_all_children(shell, pids);
	free(pids);
}

int	open_file_safe(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
		error_exit(file, 1);
	return (fd);
}
