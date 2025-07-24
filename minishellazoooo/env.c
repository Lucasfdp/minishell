#include "minishell.h"

void	execute_env(char **envp_shell)
{
	int	i;

	i = -1;
	while (envp_shell[++i])
		printf("%s\n", envp_shell[i]);
}