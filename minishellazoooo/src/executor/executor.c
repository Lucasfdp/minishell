// #include "executor.h"

// // void	duppy(int fd_input, int fd_output)
// // {
// // 	if (dup2(fd_input, STDIN_FILENO) == -1)
// // 		error_exit("dup2 input", 1);
// // 	if (dup2(fd_output, STDOUT_FILENO) == -1)
// // 		error_exit("dup2 output", 1);
// // 	if (fd_input != STDIN_FILENO)
// // 		close(fd_input);
// // 	if (fd_output != STDOUT_FILENO)
// // 		close(fd_output);
// // }

// // void	close_pipe_fds(t_pinfo *pinfo)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (i < pinfo->num_cmds - 1)
// // 	{
// // 		close(pinfo->pipes[i][0]);
// // 		close(pinfo->pipes[i][1]);
// // 		i++;
// // 	}
// // }

// // void	exec_child(char *cmd, int fd_input, int fd_output, t_pinfo *pinfo)
// // {
// // 	char	**args;
// // 	char	*cmd_path;

// // 	duppy(fd_input, fd_output);
// // 	if (pinfo->pipes)
// // 		close_pipe_fds(pinfo);
// // 	args = ft_split(cmd, ' ');
// // 	if (!args || !args[0])
// // 		error_exit("Invalid command", 127);
// // 	cmd_path = get_cmd_path(args[0], pinfo->envp);
// // 	if (!cmd_path)
// // 	{
// // 		free_array(args, -1);
// // 		error_exit("command not found", 127);
// // 	}
// // 	execve(cmd_path, args, pinfo->envp);
// // 	if (access(cmd_path, X_OK) != 0)
// // 	{
// // 		free(cmd_path);
// // 		free_array(args, -1);
// // 		error_exit("execve failed", 126);
// // 	}
// // 	free(cmd_path);
// // 	free_array(args, -1);
// // 	error_exit("execve failed", 1);
// // }

// // void	exec_single_command(t_pinfo *pinfo, pid_t pid, int i)
// // {
// // 	pid = fork();
// // 	if (pid < 0)
// // 		error_exit("fork failed", 1);
// // 	if (pid == 0)
// // 	{
// // 		if (i == 0)
// // 		{
// // 			if (pinfo->num_cmds > 1)
// // 			{
// // 				close(pinfo->pipes[i][0]);
// // 				exec_child(pinfo->cmds[i], pinfo->infile, pinfo->pipes[i][1],
// // 					pinfo);
// // 			}
// // 			else
// // 				exec_child(pinfo->cmds[i], pinfo->infile, pinfo->outfile,
// // 					pinfo);
// // 		}
// // 		else if (i == pinfo->num_cmds - 1)
// // 			exec_child(pinfo->cmds[i], pinfo->pipes[i - 1][0], pinfo->outfile,
// // 				pinfo);
// // 		else
// // 			exec_child(pinfo->cmds[i], pinfo->pipes[i - 1][0],
// // 				pinfo->pipes[i][1], pinfo);
// // 	}
// // }

// // void	exec_all(t_pinfo *pinfo, pid_t *pids)
// // {
// // 	int	i;

// // 	i = -1;
// // 	while (++i < pinfo->num_cmds)
// // 		exec_single_command(pinfo, pids[i], i);
// // }

// // void	execute_commands(t_shell *shell)
// // {
// // 	int		i;
// // 	pid_t	*pids;
// // 	int		num_cmds;

// // 	num_cmds = ft_lstsize(shell->commands);
// // 	pids = malloc(sizeof(pid_t) * num_cmds - 1);
// // 	if (!pids)
// // 		error_exit("malloc failed", 1);
// // 	exec_all(shell, pids);
// // 	i = -1;
// // 	while (++i < num_cmds - 1)
// // 	{
// // 		close(pinfo->pipes[i][0]);
// // 		close(pinfo->pipes[i][1]);
// // 	}
// // 	close(pinfo->infile);
// // 	close(pinfo->outfile);
// // 	i = -1;
// // 	while (++i < pinfo->num_cmds)
// // 		waitpid(pids[i], NULL, 0);
// // 	free(pids);
// // }

// void	closing_and_freeing_stuff(t_pinfo *pinfo)
// {
// 	int	i;

// 	i = -1;
// 	if (pinfo->infile >= 0)
// 		close(pinfo->infile);
// 	if (pinfo->outfile >= 0)
// 		close(pinfo->outfile);
// 	while (++i < pinfo->num_cmds - 1)
// 	{
// 		close(pinfo->pipes[i][0]);
// 		close(pinfo->pipes[i][1]);
// 	}
// 	i = -1;
// 	while (pinfo->pipes[++i])
// 		free(pinfo->pipes[i]);
// }

// void	error_exit(const char *msg, int error_num)
// {
// 	if (error_num == 0)
// 	{
// 		ft_printf("%s\n", msg);
// 		exit(1);
// 	}
// 	else
// 	{
// 		perror(msg);
// 		exit(error_num);
// 	}
// }

// char	*get_path_from_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 			return (envp[i] + 5);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*try_paths(char **split_paths, char *cmd)
// {
// 	char	*tmp;
// 	char	*full_path;
// 	int		i;

// 	i = 0;
// 	while (split_paths[i])
// 	{
// 		tmp = ft_strjoin_pipex(split_paths[i], "/");
// 		full_path = ft_strjoin_pipex(tmp, cmd);
// 		free(tmp);
// 		if (access(full_path, X_OK) == 0)
// 			return (full_path);
// 		free(full_path);
// 		i++;
// 	}
// 	return (NULL);
// }

// char	*get_cmd_path(char *cmd, char **envp)
// {
// 	char	**split_paths;
// 	char	*path;
// 	char	*result;

// 	if (ft_strchr(cmd, '/'))
// 	{
// 		if (access(cmd, X_OK) == 0)
// 			return (ft_strdup(cmd));
// 		return (NULL);
// 	}
// 	path = get_path_from_env(envp);
// 	if (!path)
// 		return (NULL);
// 	split_paths = ft_split(path, ':');
// 	if (!split_paths)
// 		return (NULL);
// 	result = try_paths(split_paths, cmd);
// 	free_array(split_paths, -1);
// 	return (result);
// }

// void	prep_fds(int ac, char **av, t_pinfo *pinfo)
// {
// 	pinfo->infile = open(av[1], O_RDONLY);
// 	if (pinfo->infile < 0)
// 		error_exit("infile", 1);
// 	pinfo->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (pinfo->outfile < 0)
// 		error_exit("outfile", 1);
// }

// void	prepare_hd_file(char *line, int pipe_fd[2], char *limiter)
// {
// 	int	line_len;

// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		line_len = ft_int_strlen(line);
// 		if (line[line_len - 1] == '\n')
// 			line[line_len - 1] = '\0';
// 		if (ft_strcmp(line, limiter) == 0)
// 			break ;
// 		write(pipe_fd[1], line, line_len);
// 		write(pipe_fd[1], "\n", 1);
// 		free(line);
// 		line = get_next_line(0);
// 	}
// }

// void	prep_fds_heredoc(int ac, char **av, t_pinfo *pinfo)
// {
// 	int		pipe_fd[2];
// 	char	*line;
// 	char	*limiter;

// 	line = NULL;
// 	limiter = av[2];
// 	if (pipe(pipe_fd) == -1)
// 		error_exit("pipe", 1);
// 	prepare_hd_file(line, pipe_fd, limiter);
// 	free(line);
// 	close(pipe_fd[1]);
// 	pinfo->infile = pipe_fd[0];
// 	pinfo->outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	if (pinfo->outfile < 0)
// 		error_exit("outfile", 1);
// }

// int	prep_pipes(t_pinfo *pinfo)
// {
// 	int	i;

// 	i = 0;
// 	pinfo->pipes = malloc(sizeof(int *) * (pinfo->num_cmds - 1));
// 	if (!pinfo->pipes)
// 		return (0);
// 	while (i < pinfo->num_cmds - 1)
// 	{
// 		pinfo->pipes[i] = malloc(sizeof(int) * 2);
// 		if (!pinfo->pipes[i])
// 			return (0);
// 		if (pipe(pinfo->pipes[i]) == -1)
// 			error_exit("pipe", 1);
// 		i++;
// 	}
// 	return (1);
// }

// int	prep_info(int ac, char **av, t_pinfo *pinfo, int heredoc)
// {
// 	if (heredoc)
// 	{
// 		pinfo->num_cmds = ac - 4;
// 		pinfo->cmds = copy_matrix_range(av, 3, ac - 2);
// 	}
// 	else
// 	{
// 		pinfo->num_cmds = ac - 3;
// 		pinfo->cmds = copy_matrix_range(av, 2, ac - 2);
// 	}
// 	if (!pinfo->cmds)
// 		return (0);
// 	if (pinfo->num_cmds > 1)
// 	{
// 		if (!prep_pipes(pinfo))
// 			return (0);
// 	}
// 	else
// 		pinfo->pipes = NULL;
// 	return (1);
// }