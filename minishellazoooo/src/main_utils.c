#include "minishell.h"

// void print_redirs(t_redir *redir)
// {
// 	while (redir)
// 	{
// 		printf("      redir: ");
// 		if (redir->type == REDIR_IN)
// 			printf("IN");
// 		else if (redir->type == REDIR_OUT)
// 			printf("OUT");
// 		else if (redir->type == REDIR_APPEND)
// 			printf("APPEND");
// 		else if (redir->type == REDIR_HEREDOC)
// 			printf("HEREDOC");
// 		else
// 			printf("NONE");
// 		printf(", file: %s\n", redir->file ? redir->file : "(null)");
// 		redir = redir->next;
// 	}
// }

// void print_command(t_command *cmd, int index)
// {
// 	int i = 0;

// 	printf("  Command %d:\n", index);
// 	printf("    args: ");
// 	if (cmd->args)
// 	{
// 		while (cmd->args[i])
// 		{
// 			printf("[%s] ", cmd->args[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("(none)");
// 	printf("\n");
// 	printf("    input_fd: %d\n", cmd->input_fd);
// 	printf("    output_fd: %d\n", cmd->output_fd);
// 	print_redirs(cmd->redirs);
// }

// void print_shell(t_shell *shell)
// {
// 	int i = 0;
// 	t_command *cmd;
// 	int cmd_index = 1;

// 	printf("Shell:\n");
// 	printf("  last_status: %d\n", shell->exit_status);
// 	printf("%s\n", shell->input);
// 	printf("  tokens: ");
// 	if (shell->tokens)
// 	{
// 		while (shell->tokens[i])
// 		{
// 			printf("[%s] ", shell->tokens[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		printf("(none)");
// 	printf("\n\nCommands:\n");

// 	cmd = shell->commands;
// 	while (cmd)
// 	{
// 		print_command(cmd, cmd_index++);
// 		cmd = cmd->next;
// 	}
// }

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = copy_matrix(envp);
	shell->exit_status = 0;
	shell->commands = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->token_list = NULL;
}

void	reset_shell_iteration(t_shell *shell)
{
	shell->commands = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->token_list = NULL;
}
