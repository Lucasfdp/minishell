#include "src/minishell.h"
#include "src/parsing/parsing.h"
#include "src/executor/executor.h"

static void	cleanup_validation_fail(t_shell *shell, t_token **tokens)
{
	free_array(shell->tokens);
	shell->tokens = NULL;
	free_token_list(tokens);
	shell->token_list = NULL;
}

static int	process_input(t_shell *shell, char *input)
{
	t_token	**tokens;

	shell->input = ft_strdup(input);
	tokens = tokeniser(input);
	if (!tokens)
	{
		(void)shell;
		return (0);
	}
	shell->token_list = tokens;
	expand_tokens(shell, tokens);
	shell->tokens = tokens_to_argv(tokens);
	if (!validate_tokens(shell->tokens, shell->input))
	{
		cleanup_validation_fail(shell, tokens);
		return (0);
	}
	fill_structs(shell, shell->tokens);
	free_token_list(tokens);
	shell->token_list = NULL;
	execute_commands(shell);
	return (1);
}

static void	cleanup_iteration(t_shell *shell, char *input)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free(input);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	while (1)
	{
		reset_shell_iteration(&shell);
		input = read_input2();
		if (!input)
			break ;
		process_input(&shell, input);
		cleanup_iteration(&shell, input);
	}
	free_shell(&shell);
	return (0);
}
