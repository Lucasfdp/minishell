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
	char	*cmd_path;

	cmd_path = get_cmd_path(shell, cmd);
	if (!cmd_path)
	{
		shell->exit_status = 127;
		error_exit("command not found", 127);
	}
	execve(cmd_path, cmd->args, shell->env);
	perror("execve");
	free(cmd_path);
	shell->exit_status = 126;
	exit(126);
}

static void	close_unused_pipes(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		if (shell->pipes[i][0] != cmd->input_fd)
			close(shell->pipes[i][0]);
		if (shell->pipes[i][1] != cmd->output_fd)
			close(shell->pipes[i][1]);
		i++;
	}
}

void	exec_child(t_shell *shell, t_command *cmd)
{
	if (shell->num_cmds > 1)
		close_unused_pipes(shell, cmd);
	if (cmd->redirs)
		apply_redirs(cmd);
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (cmd->input_fd >= 0 && cmd->input_fd != STDIN_FILENO)
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
			error_exit("dup2 input", 1);
	if (cmd->output_fd >= 0 && cmd->output_fd != STDOUT_FILENO)
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			error_exit("dup2 output", 1);
	if (detect_builtin(cmd->args[0]))
	{
		execute_builtins(cmd, shell);
		exit(shell->exit_status);
	}
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
