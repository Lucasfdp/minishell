/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:54:15 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:54:16 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *msg, int error_num)
{
	if (error_num == 0)
	{
		perror(msg);
		exit(1);
	}
	else
	{
		perror(msg);
		exit(error_num);
	}
}

void	free_token_list(t_token **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i])
		{
			if (tokens[i]->value)
			{
				free(tokens[i]->value);
				tokens[i]->value = NULL;
			}
			free(tokens[i]);
			tokens[i] = NULL;
		}
		i++;
	}
	free(tokens);
}

void	free_redirs(t_redir *lst)
{
	t_redir	*temp;

	while (lst)
	{
		if (lst->file)
			free(lst->file);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

void	free_commands(t_command *lst)
{
	t_command	*temp;

	while (lst)
	{
		if (lst->args)
			free_array(lst->args);
		if (lst->redirs)
			free_redirs(lst->redirs);
		if (lst->input_fd > 0)
			close(lst->input_fd);
		if (lst->output_fd > 0)
			close(lst->output_fd);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->tokens)
		free_array(shell->tokens);
	if (shell->input)
		free(shell->input);
	if (shell->env)
		free_array(shell->env);
	if (shell->commands)
		free_commands(shell->commands);
}
