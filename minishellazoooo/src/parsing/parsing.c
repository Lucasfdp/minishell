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

void prep_fds_heredoc(t_redir *redir, char *limiter)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
        error_exit("pipe", 1);
    prepare_hd_file(pipe_fd, limiter);
    close(pipe_fd[1]);
    redir->heredoc_fd = pipe_fd[0];
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
	{
		prep_fds_heredoc(redir, file_token);
		redir->file = ft_strdup(file_token);
	}
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

t_token_type get_token_type(char *token)
{
    if (!token)
        return TOKEN_WORD;
    if (ft_strcmp(token, "|") == 0)
        return TOKEN_PIPE;
    else if (ft_strcmp(token, "<") == 0)
        return TOKEN_REDIR_IN;
    else if (ft_strcmp(token, ">") == 0)
        return TOKEN_REDIR_OUT;
    else if (ft_strcmp(token, ">>") == 0)
        return TOKEN_REDIR_APPEND;
    else if (ft_strcmp(token, "<<") == 0)
        return TOKEN_HEREDOC;
    return TOKEN_WORD;
}

void	syntax_error_unexpected_token(const char *token, const char *cmd)
{
	if (token)
		ft_fprintf(STDERR_FILENO,
			"bash: -c: line 0: syntax error near unexpected token `%s'\n",
			token);
	else
		ft_fprintf(STDERR_FILENO,
			"bash: -c: line 0: syntax error near unexpected token `newline'\n");

	// Only print second line when bash would show the full input line
	if (cmd)
		ft_fprintf(STDERR_FILENO, "bash: -c: line 0: `%s'\n", cmd);
}

// returns false if invalid
bool validate_tokens(char **tokens, const char *cmdline)
{
	int i = 0;
	t_token_type prev = TOKEN_NONE;

	while (tokens[i])
	{
		t_token_type curr = get_token_type(tokens[i]);

		// PIPE at start or consecutive
		if (curr == TOKEN_PIPE)
		{
			if (i == 0 || prev == TOKEN_PIPE)
			{
				syntax_error_unexpected_token("|", cmdline); // two-line bash output
				return false;
			}
		}

		// HEREDOC without a word after
		if (curr == TOKEN_HEREDOC)
		{
			if (!tokens[i + 1] || get_token_type(tokens[i + 1]) != TOKEN_WORD)
			{
				syntax_error_unexpected_token(tokens[i + 1], NULL); // one-line bash output
				return false;
			}
		}

		// REDIRECTIONS without a word after
		if (curr == TOKEN_REDIR_IN || curr == TOKEN_REDIR_OUT || curr == TOKEN_REDIR_APPEND)
		{
			if (!tokens[i + 1] || get_token_type(tokens[i + 1]) != TOKEN_WORD)
			{
				syntax_error_unexpected_token(tokens[i + 1], cmdline); // two-line bash output
				return false;
			}
		}

		prev = curr;
		i++;
	}

	// Cannot end with a pipe
	if (prev == TOKEN_PIPE)
	{
		syntax_error_unexpected_token(NULL, cmdline); // two-line bash output
		return false;
	}

	return true;
}

void fill_structs(t_shell *shell, char **tokens)
{
	int i = 0;
	int type;
	t_command *command = init_command();
	t_token_type prev_type = TOKEN_NONE;

	if (!command)
		return;

	while (tokens[i])
	{
		type = is_redir(tokens[i]);

		// PIPE handling
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			if (!command->args && !command->redirs)
			{
				syntax_error_unexpected_token("|", shell->input); // two-line
				free(command);
				shell->exit_status = 2;
				return;
			}
			add_command(shell, command);
			command = init_command();
			if (!command)
				return;
			prev_type = TOKEN_PIPE;
			i++;
			continue;
		}

		// HEREDOC handling
		if (type == REDIR_HEREDOC)
		{
			if (!tokens[i + 1] || is_redir(tokens[i + 1]) != REDIR_NONE)
			{
				syntax_error_unexpected_token(tokens[i + 1], NULL); // one-line
				free(command);
				shell->exit_status = 2;
				return;
			}
			add_redir(command, type, tokens[i + 1]);
			i += 2;
			continue;
		}

		// OTHER redirections: <, >, >>
		if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND)
		{
			if (!tokens[i + 1] || is_redir(tokens[i + 1]) != REDIR_NONE)
			{
				syntax_error_unexpected_token(tokens[i + 1], shell->input); // two-line
				free(command);
				shell->exit_status = 2;
				return;
			}
			add_redir(command, type, tokens[i + 1]);
			i += 2;
			continue;
		}

		// NORMAL ARGUMENT
		command->args = add_arg(command->args, tokens[i]);
		prev_type = TOKEN_WORD;
		i++;
	}

	// Cannot end with a pipe
	if (prev_type == TOKEN_PIPE)
	{
		syntax_error_unexpected_token(NULL, shell->input); // two-line
		free(command);
		shell->exit_status = 2;
		return;
	}

	// Append last command if it has args or redirections
	if (command->args || command->redirs)
		add_command(shell, command);
	else
		free(command);
}

// void fill_structs(t_shell *shell, char **tokens)
// {
//     int i = 0;
//     t_command *command = init_command();
//     t_token_type prev_type = TOKEN_NONE;
//     int type;

//     if (!command)
//         return;

//     while (tokens[i])
//     {
//         type = is_redir(tokens[i]);

//         // PIPE
//         if (ft_strcmp(tokens[i], "|") == 0)
//         {
//             if (!command->args && !command->redirs)
//             {
//                 syntax_error_unexpected_token("|", shell->input);
//                 free(command);
//                 shell->exit_status = 2;
//                 return;
//             }
//             add_command(shell, command);
//             command = init_command();
//             if (!command)
//                 return;
//             prev_type = TOKEN_PIPE;
//             i++;
//             continue;
//         }

//         // HEREDOC
//         if (type == REDIR_HEREDOC)
//         {
//             if (!tokens[i + 1] || is_redir(tokens[i + 1]) != REDIR_NONE)
//             {
//                 syntax_error_unexpected_token(tokens[i + 1], NULL);
//                 free(command);
//                 shell->exit_status = 2;
//                 return;
//             }
//             add_redir(command, type, tokens[i + 1]);
//             i += 2;
//             continue;
//         }

//         // OTHER REDIRECTIONS
//         if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND)
//         {
//             if (!tokens[i + 1] || is_redir(tokens[i + 1]) != REDIR_NONE)
//             {
//                 syntax_error_unexpected_token(tokens[i + 1], shell->input);
//                 free(command);
//                 shell->exit_status = 2;
//                 return;
//             }
//             add_redir(command, type, tokens[i + 1]);
//             i += 2;
//             continue;
//         }

//         // NORMAL ARG
//         if (tokens[i] && ft_strlen(tokens[i]) > 0)
//             command->args = add_arg(command->args, tokens[i]);

//         prev_type = TOKEN_WORD;
//         i++;
//     }

//     // Cannot end with PIPE
//     if (prev_type == TOKEN_PIPE)
//     {
//         syntax_error_unexpected_token(NULL, shell->input);
//         free(command);
//         shell->exit_status = 2;
//         return;
//     }

//     if (command->args || command->redirs)
//         add_command(shell, command);
//     else
//         free(command);
// }
