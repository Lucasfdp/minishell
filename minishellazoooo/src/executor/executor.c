#include "executor.h"

void	duppy(int fd_input, int fd_output)
{
	if (dup2(fd_input, STDIN_FILENO) == -1)
		error_exit("dup2 input", 1);
	if (dup2(fd_output, STDOUT_FILENO) == -1)
		error_exit("dup2 output", 1);
	if (fd_input != STDIN_FILENO)
		close(fd_input);
	if (fd_output != STDOUT_FILENO)
		close(fd_output);
}

void	apply_redirs(t_command *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_OUT)
		{
			fd = open(r->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
				error_exit(r->file, 1);
			if (dup2(fd, STDOUT_FILENO) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		else if (r->type == REDIR_APPEND)
		{
			fd = open(r->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd < 0)
				error_exit(r->file, 1);
			if (dup2(fd, STDOUT_FILENO) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		else if (r->type == REDIR_IN)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				error_exit(r->file, 1);
			if (dup2(fd, STDIN_FILENO) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		else if (r->type == REDIR_HEREDOC)
		{
			if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
				error_exit("dup2 heredoc", 1);
			close(r->heredoc_fd);
		}
		r = r->next;
	}
}

bool	has_heredoc(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
			return (true);
		r = r->next;
	}
	return (false);
}

void	set_pipe_fds(t_shell *shell)
{
	t_command	*cmd;
	int			i;

	cmd = shell->commands;
	i = 0;
	while (cmd)
	{
		if (i == 0 && shell->num_cmds > 1)
			cmd->output_fd = shell->pipes[0][1];
		else if (i == shell->num_cmds - 1 && shell->num_cmds > 1)
			cmd->input_fd = shell->pipes[i - 1][0];
		else if (shell->num_cmds > 2)
		{
			cmd->input_fd = shell->pipes[i - 1][0];
			cmd->output_fd = shell->pipes[i][1];
		}
		cmd = cmd->next;
		i++;
	}
}

void	setup_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	shell->num_cmds = ft_lstsize_2(shell->commands);
	if (shell->num_cmds < 2)
		return ;
	shell->pipes = malloc(sizeof(int *) * (shell->num_cmds - 1));
	if (!shell->pipes)
		error_exit("malloc pipes", 1);
	while (i < shell->num_cmds - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i] || pipe(shell->pipes[i]) == -1)
			error_exit("pipe", 1);
		i++;
	}
	set_pipe_fds(shell);
}
