#include "minishell.h"

void	execute_pwd(void)
{
	char	*pwd = getcwd(NULL, 0);

	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	else
		perror("getcwd");
}
