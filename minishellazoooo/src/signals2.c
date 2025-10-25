/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 05:48:34 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/25 05:48:35 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc_interrupt(int status, t_shell *shell)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		g_sigint_received = 1;
		return (1);
	}
	return (0);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sigint_received = 1;
}

void	setup_signals_child(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals_heredoc(void)
{
	g_sigint_received = 0;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
