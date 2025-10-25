/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 04:28:12 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/25 05:48:32 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	exit(130);
}

void	setup_signals_interactive(void)
{
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_parent(void)
{
	signal(SIGINT, handle_sigint_parent);
	signal(SIGQUIT, SIG_IGN);
}
