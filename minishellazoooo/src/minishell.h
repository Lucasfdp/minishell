/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:53:47 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/25 05:48:11 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "builtins/builtins.h"
# include "executor/executor.h"
# include "parsing/parsing.h"

extern volatile sig_atomic_t	g_sigint_received;

extern void	rl_replace_line(const char *text, int clear_undo);
extern int	rl_on_new_line(void);
extern void	rl_redisplay(void);

typedef struct s_quote_state
{
	int	single_q;
	int	double_q;
}	t_quote_state;

typedef struct s_buf_state
{
	char	*buf;
	int		*k;
}	t_buf_state;

typedef struct s_quote_flags
{
	int	in_single;
	int	in_double;
}	t_quote_flags;

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

typedef struct s_validate_ctx
{
	char			**tokens;
	t_token_type	curr;
	t_token_type	prev;
	const char		*cmdline;
}	t_validate_ctx;

typedef struct s_token
{
	char	*value;
	int		in_single;
	int		in_double;
}	t_token;

typedef struct s_tok_state
{
	t_token			**tokens;
	int				*index;
	char			*buf;
	t_quote_state	qs;
}	t_tok_state;

typedef enum e_redir_type
{
	REDIR_NONE = -1,
	REDIR_IN = 0,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir_params
{
	t_redir_type	type;
	char			*file_token;
	int				should_expand;
}	t_redir_params;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				heredoc_fd;
	int				expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command		t_command;

struct s_command
{
	char		**args;
	int			input_fd;
	int			output_fd;
	t_redir		*redirs;
	t_command	*next;
};

typedef struct s_parse_state
{
	t_command		**cmd;
	t_token_type	*prev;
}	t_parse_state;

typedef struct s_shell
{
	char		**env;
	int			exit_status;
	char		*input;
	t_token		**token_list;
	char		**tokens;
	int			**pipes;
	int			num_cmds;
	t_command	*commands;
}	t_shell;

// readline functions
char		*read_input(const char *prompt);
char		*read_input2(void);
void		setup_signals_parent(void);
void		handle_sigint_interactive(int sig);
void		handle_sigint_parent(int sig);
void		handle_sigint_child(int sig);
void		setup_signals_interactive(void);
void		setup_signals_parent(void);
void		setup_signals_child(void);
void		setup_signals_heredoc(void);
int			check_heredoc_interrupt(int status, t_shell *shell);

// freeing functions
void		free_redirs(t_redir *lst);
void		free_commands(t_command *lst);
void		free_shell(t_shell *shell);
void		error_exit(const char *msg, int error_num);
void		free_token_list(t_token **tokens);
void		init_shell(t_shell *shell, char **envp);
void		reset_shell_iteration(t_shell *shell);

#endif
