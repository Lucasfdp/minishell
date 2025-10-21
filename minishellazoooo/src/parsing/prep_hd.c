#include "parsing.h"

void	prep_fds_heredoc(t_redir *redir, char *limiter, int should_expand,
			t_shell *shell)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error_exit("pipe", 1);
	redir->expand = should_expand;
	prepare_hd_file(pipe_fd, limiter, should_expand, shell);
	close(pipe_fd[1]);
	redir->heredoc_fd = pipe_fd[0];
}

void	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static void	write_heredoc_line(int fd, char *line, int should_expand,
					t_shell *shell)
{
	char	*expanded;

	if (should_expand)
	{
		expanded = expand_variables(shell, line, 0);
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

void	prepare_hd_file(int pipe_fd[2], char *limiter, int should_expand,
			t_shell *shell)
{
	char	*line;

	line = get_next_line(0);
	while (line != NULL)
	{
		strip_newline(line);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(pipe_fd[1], line, should_expand, shell);
		free(line);
		line = get_next_line(0);
	}
}

int	has_unclosed_quotes(t_quote_state *qs)
{
	char	*msg;

	msg = "bash: -c: line 0: unexpected EOF while looking for matching `''\n";
	if (qs->single_q || qs->double_q)
	{
		ft_fprintf(STDERR_FILENO, msg);
		ft_fprintf(STDERR_FILENO,
			"bash: -c: line 1: syntax error: unexpected end of file\n");
		return (1);
	}
	return (0);
}
