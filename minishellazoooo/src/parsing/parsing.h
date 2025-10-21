#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_quote_state	t_quote_state;

typedef struct s_redir_params	t_redir_params;

typedef struct s_tok_state		t_tok_state;

typedef enum e_token_type		t_token_type;

typedef struct s_validate_ctx 	t_validate_ctx;

typedef struct s_token			t_token;

typedef enum e_redir_type		t_redir_type;

typedef struct s_parse_state	t_parse_state;

typedef struct s_redir			t_redir;

int				count_tokens(char *input);
t_token			**tokeniser(char *input);
char			**tokens_to_argv(t_token **tokens);
t_token_type	get_token_type(char *token);
char			*expand_variables(t_shell *shell, char *token, int in_double);
void			expand_tokens(t_shell *shell, t_token **tokens);
t_command		*init_command(void);
int				add_command(t_shell *shell, t_command *command);
t_redir_type	is_redir(char *token);
int				add_redir(t_command *command, t_redir_params *params,
					t_shell *shell);
char			**add_arg(char **cmd_args, char *arg);
void			fill_structs(t_shell *shell, char **tokens);
bool			validate_tokens(char **tokens, const char *cmdline);
int				array_len(char **array);
void			syntax_error_unexpected_token(const char *token,
					const char *cmd);
void			prep_fds_heredoc(t_redir *redir, char *limiter,
					int should_expand, t_shell *shell);
void			prepare_hd_file(int pipe_fd[2], char *limiter,
					int should_expand, t_shell *shell);
int				skip_whitespace(char *input, int i);
int				is_operator_char(char c);
int				handle_operator(char *input, int i, t_token **tokens, int j);
int				process_backslash(char *input, int i, char *buf, int *k,
					int dq);
int				process_word_char(char *in, int i, char *buf, int *k,
					t_quote_state *qs);
int				extract_word_to_buf(char *in, int i, char *buf,
					t_quote_state *qs);
void			create_token_from_buf(char *buf, t_token **tokens, int j,
					int ss, int sd);
char			*expand_variables(t_shell *shell, char *token, int in_double);
int				expand_dollar(t_shell *shell, char *token, int i,
					char **result);
int				expand_env_var(char *token, int i, char **result,
					t_shell *shell);
int				expand_exit_status(t_shell *shell, char **result);
int				expand_backslash(char *token, int i, char **result,
					int in_double);
char			*ft_strjoin_char(char *s, char c);
char			*strjoin_char_free(char *str, char c);
char			*get_env_value(char **envp, const char *var);
char			*strjoin_free(char *str, char *to_add);
bool			is_redir_type(int type);
bool			validate_next_redir_token(char **tokens, int i);
void			do_error_stuff(t_shell *shell, char *token, t_command **cmd);
bool			validate_current_token(char **tokens, int i, t_token_type curr,
					t_token_type prev, const char *cmdline);
int				has_unclosed_quotes(t_quote_state *qs);
char			*alloc_tokeniser_resources(t_token ***tokens, char *input);
char			**no_args(char *arg);
void			init_parse_state(t_parse_state *ps, t_command **cmd,
					t_token_type *prev);

#endif