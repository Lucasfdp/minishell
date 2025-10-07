#include "parsing.h"
#include "minishell.h"

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

void prepare_hd_file(int pipe_fd[2], char *limiter)
{
    char *line;

    while ((line = get_next_line(0)))
    {
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (ft_strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
}

void prep_fds_heredoc(t_command *cmd, char *limiter)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
        error_exit("pipe", 1);
    prepare_hd_file(pipe_fd, limiter);
    close(pipe_fd[1]);              // close writer
    cmd->input_fd = pipe_fd[0];     // keep reader
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
	redir->type = type;
	if (type == REDIR_HEREDOC)
		prep_fds_heredoc(command, file_token);
	else 
		redir->file = ft_strdup(file_token);
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

void	copy_args(char **src, char **dest)
{
	int i;
	
	if (!src || !dest)
		return;
	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**add_arg(char **cmd_args, char *arg)
{
	int		i;
	int 	j;
	char	**new_args;

	if (!cmd_args)
	{
		new_args = malloc(sizeof(char *) * 2);
		if (!new_args)
			return (NULL);
		new_args[0] = ft_strdup(arg);
		new_args[1] = NULL;
		return (new_args);
	}
	i = 0;
	while (cmd_args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (NULL);
	j = -1;
	while (++j < i)
		new_args[j] = ft_strdup(cmd_args[j]);
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free_map(cmd_args, array_len(cmd_args));
	return (new_args);
}

void	fill_structs(t_shell *shell, char **tokens)
{
	int			i;
	int			type;
	t_command	*command;

	i = 0;
	command = init_command();
	if (!command)
		return ; // error stuffs
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			// finalize and append command
			if (!command->args && !command->redirs)
			{
				// syntax error (empty command before pipe)
				free(command);
				return ;
			}
			add_command(shell, command);
			command = init_command();
			if (!command)
				return ;
			i++;
			continue;
		}
		type = is_redir(tokens[i]);
		if (type != REDIR_NONE)
		{
			if (!tokens[i + 1])
			{
				// syntax error: missing filename
				free(command);
				return ;
			}
			add_redir(command, type, tokens[i + 1]);
			i += 2;
			continue;
		}
		command->args = add_arg(command->args, tokens[i]);
		i++;
	}
	if (command->args || command->redirs)
		add_command(shell, command);
	else
		free(command);
}
