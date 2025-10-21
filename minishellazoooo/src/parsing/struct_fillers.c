/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fillers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:54:53 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:54:54 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command	*init_command(void)
{
	t_command	*command;

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
	t_command	*last;

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

static void	append_redir(t_command *command, t_redir *redir)
{
	t_redir	*redir_last;

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
}

int	add_redir(t_command *command, t_redir_params *params, t_shell *shell)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = params->type;
	if (params->type == REDIR_HEREDOC)
	{
		prep_fds_heredoc(redir, params->file_token, params->should_expand,
			shell);
		redir->file = ft_strdup(params->file_token);
	}
	else
		redir->file = ft_strdup(params->file_token);
	append_redir(command, redir);
	return (1);
}

char	**no_args(char *arg)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * 2);
	if (!new_args)
		return (NULL);
	new_args[0] = ft_strdup(arg);
	new_args[1] = NULL;
	return (new_args);
}
