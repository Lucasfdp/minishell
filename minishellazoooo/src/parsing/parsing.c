#include "parsing.h"

void	fill_structs(t_shell *shell, char **tokens)
{
	int	i;
	t_command	*command;
	
	i = 0;
	command = init_command();
	if (!command)
		// error stuffs
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2))
		{
			add_command(shell, command);

		}
		else if (is_redir(tokens[i]) != -1)
		{
			add_redir(command, is_redir(tokens[i]), tokens[i + 1]);
		}
		else
			add_arg(command);
	}
}

t_command	*init_command()
{
	t_command *command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->input_fd = STDIN_FILENO;
	command->output_fd = STDOUT_FILENO;
	command->redirs = NULL;
	command->next = NULL;
	return (command);
}

int	add_command(t_shell *shell, t_command *command)
{
	t_command *last;

	if (!command)
		return (0);
	last = shell->commands;
	if (!last)
		shell->commands = command;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = command;
	}
	return (1);
}

t_redir_type	is_redir(char *token)
{
	if (ft_strncmp(token, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (REDIR_HEREDOC);
	else
		return (REDIR_NONE);
}

int	add_redir(t_command *command, t_redir_type type, char *file_token)
{
	t_redir *redir;
	t_redir *redir_last;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->file = ft_strdup(file_token);
	redir->type = type;
	redir_last = command->redirs;
	redir->next = NULL;
	if (!redir_last)
		command->redirs = redir;
	else
	{
		while (redir_last->next != NULL)
			redir_last = redir_last->next;
		redir_last->next = redir;
	}
	return (1);
}

int	add_arg(t_command *command)
{

}