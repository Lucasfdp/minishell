#include "executor.h"

void	close_all_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	use_execve(t_shell *shell, t_command *cmd)
{
	char *cmd_path;

	cmd_path = get_cmd_path(shell, cmd);
	if (!cmd_path)
		error_exit("command not found", 127);
	execve(cmd_path, cmd->args, shell->env);
	perror("execve");
	free(cmd_path);
	exit(126);
}

void	exec_child(t_shell *shell, t_command *cmd)
{
	int	i = 0;

	while (i < shell->num_cmds - 1)
	{
		if (shell->pipes[i][0] != cmd->input_fd)
			close(shell->pipes[i][0]);
		if (shell->pipes[i][1] != cmd->output_fd)
			close(shell->pipes[i][1]);
		i++;
	}
	if (cmd->redirs)
		apply_redirs(cmd);
	if (cmd->input_fd != STDIN_FILENO)
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			error_exit("dup2 input", 1);
	if (cmd->output_fd != STDOUT_FILENO)
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			error_exit("dup2 output", 1);
	if (detect_builtin(cmd->args[0]))
		execute_builtins(cmd, shell);
	else
		use_execve(shell, cmd);
}

void	fork_that(t_shell *shell, t_command *cmd, pid_t *pids)
{
	int	i;

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

void	execute_commands(t_shell *shell)
{
	pid_t		*pids;
	t_command	*cmd;
	int			i;

	shell->num_cmds = ft_lstsize_2(shell->commands);
	pids = malloc(sizeof(pid_t) * shell->num_cmds);
	if (!pids)
	error_exit("malloc pids", 1);
	cmd = shell->commands;
	if (shell->num_cmds == 1 && detect_builtin(cmd->args[0]))
	{	
		execute_builtins(cmd, shell);
		exit(0);
	}
	if (shell->num_cmds > 1)
		setup_pipes(shell);
	fork_that(shell, cmd, pids);
	if (shell->num_cmds > 1)
		close_all_pipes(shell);
	i = 0;
	while (i < shell->num_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}
