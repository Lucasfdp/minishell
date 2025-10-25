/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:53:52 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/25 05:05:46 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = copy_matrix(envp);
	shell->exit_status = 0;
	shell->input = NULL;
	shell->token_list = NULL;
	shell->tokens = NULL;
	shell->pipes = NULL;
	shell->num_cmds = 0;
	shell->commands = NULL;
}

void	reset_shell_iteration(t_shell *shell)
{
	shell->commands = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->token_list = NULL;
}
