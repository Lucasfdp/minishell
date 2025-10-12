#include "src/minishell.h"
#include "src/parsing/parsing.h"
#include "src/executor/executor.h"

static void print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf("      redir: ");
		if (redir->type == REDIR_IN)
			printf("IN");
		else if (redir->type == REDIR_OUT)
			printf("OUT");
		else if (redir->type == REDIR_APPEND)
			printf("APPEND");
		else if (redir->type == REDIR_HEREDOC)
			printf("HEREDOC");
		else
			printf("NONE");
		printf(", file: %s\n", redir->file ? redir->file : "(null)");
		redir = redir->next;
	}
}

static void print_command(t_command *cmd, int index)
{
	int i = 0;

	printf("  Command %d:\n", index);
	printf("    args: ");
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			printf("[%s] ", cmd->args[i]);
			i++;
		}
	}
	else
		printf("(none)");
	printf("\n");
	printf("    input_fd: %d\n", cmd->input_fd);
	printf("    output_fd: %d\n", cmd->output_fd);
	print_redirs(cmd->redirs);
}

void print_shell(t_shell *shell)
{
	int i = 0;
	t_command *cmd;
	int cmd_index = 1;

	printf("Shell:\n");
	printf("  last_status: %d\n", shell->exit_status);
	printf("%s\n", shell->input);
	printf("  tokens: ");
	if (shell->tokens)
	{
		while (shell->tokens[i])
		{
			printf("[%s] ", shell->tokens[i]);
			i++;
		}
	}
	else
		printf("(none)");
	printf("\n\nCommands:\n");

	cmd = shell->commands;
	while (cmd)
	{
		print_command(cmd, cmd_index++);
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*input;
	t_shell	shell;
	t_token **tokens;

	shell.env = copy_matrix(envp);
	shell.exit_status = 0;
	while (1)
	{
		shell.commands = NULL;
		//input = read_input("minishell$ ");
		input = read_input2();
		if (!input)
			break;
		// shell.input = ft_strdup(input);
		// tokens = tokeniser(input);
		// expand_tokens(&shell, tokens);
		// shell.tokens = tokens_to_argv(tokens);
		// fill_structs(&shell, shell.tokens);
		// print_shell(&shell);
		shell.input = ft_strdup(input);
		tokens = tokeniser(input);
		if (!tokens)
		{
			free(shell.input);
			shell.input = NULL;
			free(input);
			continue;
		}
		expand_tokens(&shell, tokens);
		shell.tokens = tokens_to_argv(tokens);
		if (!validate_tokens(shell.tokens, shell.input))
		{
			free_array(shell.tokens);
			free_token_list(tokens);
			free(shell.input);
			shell.input = NULL;
			free(input);
			continue;
		}
	    fill_structs(&shell, shell.tokens);
	    free_token_list(tokens);
		execute_commands(&shell);
		//free_shell(&shell);
		if (input)
			free(input);
	}
	return (0);
}

