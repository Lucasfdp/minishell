#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing/parsing.h"
# include "builtins/builtins.h"

extern void rl_replace_line(const char *text, int clear_undo);
extern int rl_on_new_line(void);
extern void rl_redisplay(void);


typedef struct s_shell
{
	char	**env;
	int		last_status;
}	t_shell;

typedef struct s_tokens
{

}	t_tokens;


// readline functions
char 	*read_input(const char *prompt);
void 	setup_signals(void);
void 	handle_sigint(int sig);

#endif
