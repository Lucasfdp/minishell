#include "minishell.h"
#include "parsing.h"

void	do_error_stuff(t_shell *shell, char *token, t_command **cmd)
{
	syntax_error_unexpected_token(token, shell->input);
	free((*cmd));
	shell->exit_status = 2;
}

bool	is_redir_type(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == REDIR_HEREDOC);
}

bool	validate_next_redir_token(char **tokens, int i)
{
	if (!tokens[i + 1] || is_redir(tokens[i + 1]) != REDIR_NONE)
		return (false);
	return (true);
}

char	*alloc_tokeniser_resources(t_token ***tokens, char *input)
{
	char	*buf;

	*tokens = malloc(sizeof(t_token *) * (count_tokens(input) + 1));
	buf = malloc(ft_int_strlen(input) + 1);
	if (!(*tokens) || !buf)
		return (NULL);
	return (buf);
}

char	**add_arg(char **cmd_args, char *arg)
{
	int		i;
	int		j;
	char	**new_args;

	if (!cmd_args)
	{
		new_args = no_args(arg);
		free_map(cmd_args, array_len(cmd_args));
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
