#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"

int				count_tokens(char *input);
t_token			**tokeniser(char *input);
char			**tokens_to_argv(t_token **tokens);
char			*expand_variables(t_shell *shell, char *token);
void			expand_tokens(t_shell *shell, t_token **tokens);
t_command		*init_command();
int				add_command(t_shell *shell, t_command *command);
t_redir_type	is_redir(char *token);
int				add_redir(t_command *command, t_redir_type type, char *file_token);
void			copy_args(char **src, char **dest);
char			**add_arg(char **cmd_args, char *arg);
void			fill_structs(t_shell *shell, char **tokens);
bool			validate_tokens(char **tokens, const char *cmdline);

#endif