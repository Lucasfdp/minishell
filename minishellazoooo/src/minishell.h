#ifndef MINISHELL_H
#define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "builtins/builtins.h"

extern void rl_replace_line(const char *text, int clear_undo);
extern int rl_on_new_line(void);
extern void rl_redisplay(void);

typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
    char *value;
    int in_single;
    int in_double;
}   t_token;

typedef enum e_redir_type
{
	REDIR_NONE = -1,
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}   t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				heredoc_fd;
	struct s_redir	*next;
} t_redir;


typedef struct s_command t_command;

struct s_command
{
	char        **args;
	int         input_fd;
	int         output_fd;
	t_redir     *redirs;
	t_command   *next;
};

typedef struct s_shell
{
	char	    **env;
	int		    exit_status;
	char		*input;
	char	    **tokens;
	int			**pipes;
	int			num_cmds;
	t_command	*commands;
}	t_shell;



// readline functions
char 	*read_input(const char *prompt);
char	*read_input2(void);
void 	setup_signals(void);
void 	handle_sigint(int sig);

// freeing functions
void	free_redirs(t_redir *lst);
void	free_commands(t_command *lst);
void    free_shell(t_shell *shell);
void	error_exit(const char *msg, int error_num);
void 	free_token_list(t_token **tokens);

#endif
