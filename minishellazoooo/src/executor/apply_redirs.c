/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:57:45 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:57:46 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	handle_redir_out(t_redir *r)
{
	int	fd;

	fd = open_file_safe(r->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	dup_and_close(fd, STDOUT_FILENO);
}

static void	handle_redir_append(t_redir *r)
{
	int	fd;

	fd = open_file_safe(r->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	dup_and_close(fd, STDOUT_FILENO);
}

static void	handle_redir_in(t_redir *r)
{
	int	fd;

	fd = open_file_safe(r->file, O_RDONLY, 0);
	dup_and_close(fd, STDIN_FILENO);
}

static void	handle_heredoc(t_redir *r)
{
	if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
		error_exit("dup2 heredoc", 1);
	close(r->heredoc_fd);
}

void	apply_redirs(t_command *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_OUT)
			handle_redir_out(r);
		else if (r->type == REDIR_APPEND)
			handle_redir_append(r);
		else if (r->type == REDIR_IN)
			handle_redir_in(r);
		else if (r->type == REDIR_HEREDOC)
			handle_heredoc(r);
		r = r->next;
	}
}
