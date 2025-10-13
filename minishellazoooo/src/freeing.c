#include "minishell.h"

void free_token_list(t_token **tokens)
{
    int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
    {
        if (tokens[i]->value)
            free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

// void free_array_shell(char **arr)
// {
//     if (!arr)
// 		return;
//     for (int i = 0; arr[i]; i++)
// 	{
//         printf("freeing arr[%d] = %p (%s)\n", i, arr[i], arr[i]);
//         free(arr[i]);
//     }
//     printf("freeing array ptr %p\n", arr);
//     free(arr);
// }

void	free_redirs(t_redir *lst)
{
	t_redir	*temp;

	while (lst != NULL)
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

	while (lst != NULL)
	{
		if (lst->args)
			free_array(lst->args);
		if (lst->redirs)
			free_redirs(lst->redirs);
		// close(lst->input_fd);
		// close(lst->output_fd);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->tokens)
		free_array(shell->tokens);
	if (shell->input)
		free(shell->input);
	// if (shell->env)
	// 	free_array_shell(shell->env);
	if (shell->commands)
		free_commands(shell->commands);
}

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
