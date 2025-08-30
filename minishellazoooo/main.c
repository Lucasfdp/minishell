#include "src/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char	*input;
	t_shell	shell;
	int	i = 0;

	shell.env = copy_matrix(envp);
	while (1)
	{
		input = read_input("minishell$ ");
		if (!input)
			break;

		// TODO: parsing, execution, etc.
		execute_builtins(input, &shell);
		shell.tokens = tokeniser(input);
		i = 0;
		while (shell.tokens[i])
		{
			printf("%s\n", shell.tokens[i]);
			i++;
		}
		free(input);
	}
	return (0);
}
