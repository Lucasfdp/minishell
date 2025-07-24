#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*input;
	t_shell	shell;

	shell.env = copy_matrix(envp);
	while (1)
	{
		input = read_input("minishell$ ");
		if (!input)
			break;

		// TODO: parsing, execution, etc.
		if (tokeniser(input))
		execute_builtins(input, &shell);
		free(input);
	}
	return (0);
}
