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
	int		count;
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
		if (r->type == REDIR_OUT) // >
		{
			fd = open(r->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
				error_exit(r->file, 1);
			if (dup2(fd, STDOUT_FILENO) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		else if (r->type == REDIR_APPEND) // >>
		{
			fd = open(r->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd < 0)
				error_exit(r->file, 1);
			if (dup2(fd, STDOUT_FILENO) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		else if (r->type == REDIR_IN) // <
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
				error_exit(r->file, 1);
			if (dup2(fd, STDIN_FILENO) == -1)
				error_exit("dup2", 1);
			close(fd);
		}
		else if (r->type == REDIR_HEREDOC) // <<
		{
			// heredoc is already prepared in prep_fds_heredoc()
			if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
				error_exit("dup2", 1);
			close(cmd->input_fd);
		}
		r = r->next;
	}
}

// void apply_redirs(t_command *cmd)
// {
// 	t_redir *r;
// 	int fd;

// 	r = cmd->redirs;
// 	while (r)
// 	{
// 		if (r->type == REDIR_OUT) // >
// 		{
// 			fd = open(r->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 			if (fd < 0)
// 				error_exit(r->file, 1);
// 			if (dup2(fd, STDOUT_FILENO) == -1)
// 				error_exit("dup2", 1);
// 			close(fd);
// 		}
// 		else if (r->type == REDIR_APPEND) // >>
// 		{
// 			fd = open(r->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
// 			if (fd < 0)
// 				error_exit(r->file, 1);
// 			if (dup2(fd, STDOUT_FILENO) == -1)
// 				error_exit("dup2", 1);
// 			close(fd);
// 		}
// 		else if (r->type == REDIR_IN) // <
// 		{
// 			fd = open(r->file, O_RDONLY);
// 			if (fd < 0)
// 				error_exit(r->file, 1);
// 			if (dup2(fd, STDIN_FILENO) == -1)
// 				error_exit("dup2", 1);
// 			close(fd);
// 		}
// 		else if (r->type == REDIR_HEREDOC) // <<
// 		{
// 			// assuming you've already written heredoc content to a pipe/fd
// 			fd = open(r->file, O_RDONLY);
// 			if (fd < 0)
// 				error_exit(r->file, 1);
// 			if (dup2(fd, STDIN_FILENO) == -1)
// 				error_exit("dup2", 1);
// 			close(fd);
// 		}
// 		r = r->next;
// 	}
// }

void setup_pipes(t_shell *shell)
{
	int i;
	t_command *cmd;

	if (shell->num_cmds == 1)
		return;

	shell->pipes = malloc(sizeof(int *) * (shell->num_cmds - 1));
	if (!shell->pipes)
		error_exit("malloc pipes", 1);

	i = 0;
	while (i < shell->num_cmds - 1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i] || pipe(shell->pipes[i]) == -1)
			error_exit("pipe", 1);
		i++;
	}

	cmd = shell->commands;
	i = 0;
	while (cmd)
	{
		// default FDs
		cmd->input_fd = STDIN_FILENO;
		cmd->output_fd = STDOUT_FILENO;

		if (i == 0 && shell->num_cmds > 1)
			cmd->output_fd = shell->pipes[0][1];
		else if (i == shell->num_cmds - 1 && shell->num_cmds > 1)
			cmd->input_fd = shell->pipes[i - 1][0];
		else if (i > 0)
		{
			cmd->input_fd = shell->pipes[i - 1][0];
			cmd->output_fd = shell->pipes[i][1];
		}
		cmd = cmd->next;
		i++;
	}
}

void close_all_pipes(t_shell *shell)
{
	int i = 0;

	while (i < shell->num_cmds - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
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

void exec_child(t_shell *shell, t_command *cmd)
{
	char *cmd_path;

	// set up pipes first
	duppy(cmd->input_fd, cmd->output_fd);

	// apply any redirections (override pipes)
	if (cmd->redirs)
		apply_redirs(cmd);

	// close all pipes in child
	if (shell->num_cmds > 1)
		close_all_pipes(shell);

	if (detect_builtin(cmd->args[0]))
		execute_builtins(cmd, shell);
	else
	{
		// find executable
		cmd_path = get_cmd_path(shell, cmd);
		if (!cmd_path)
			error_exit("command not found", 127);
		execve(cmd_path, cmd->args, shell->env);
		perror("execve"); // only reached if execve fails
		free(cmd_path);
		exit(126);
	}
}


void execute_commands(t_shell *shell)
{
	pid_t *pids;
	t_command *cmd;
	int i;

	shell->num_cmds = ft_lstsize_2(shell->commands);
	pids = malloc(sizeof(pid_t) * shell->num_cmds);
	if (!pids)
		error_exit("malloc pids", 1);

	setup_pipes(shell);

	cmd = shell->commands;
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			error_exit("fork", 1);
		if (pids[i] == 0) // child
			exec_child(shell, cmd);
		cmd = cmd->next;
		i++;
	}

	// parent closes pipes
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
