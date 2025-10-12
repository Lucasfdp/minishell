#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_input(const char *prompt)
{
	char	*line;

	setup_signals();
	line = readline(prompt);
	if (!line)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

char	*read_input2(void)
{
	char	*line;

	setup_signals();

	if (isatty(STDIN_FILENO))
		line = readline("minishell$ ");
	else
		line = get_next_line(STDIN_FILENO);

	if (!line)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "exit\n", 5);
		return (NULL);
	}

	// remove trailing newline for get_next_line() mode
	if (!isatty(STDIN_FILENO))
	{
		size_t len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
	}

	if (*line && isatty(STDIN_FILENO))
		add_history(line);

	return (line);
}
