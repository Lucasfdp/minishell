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

typedef enum e_redir_type
{
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
    REDIR_HEREDOC
}   t_redir_type;

typedef struct s_redir
{
    t_redir_type type;
    char         *file;
    struct s_redir *next;
}   t_redir;

typedef struct s_commands
{
	char	**args;
	t_redir	*redirs;
}	t_commands;

typedef struct s_shell
{
	char	**env;
	int		last_status;
	char	**tokens;
	t_commands	**commands;
}	t_shell;



// readline functions
char 	*read_input(const char *prompt);
void 	setup_signals(void);
void 	handle_sigint(int sig);

#endif
