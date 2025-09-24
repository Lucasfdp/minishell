#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"

int				count_tokens(char *input);
char			**tokeniser(char *input);
t_command		*init_command();
int				add_command(t_shell *shell, t_command *command);
t_redir_type	is_redir(char *token);
int				add_redir(t_command *command, t_redir_type type, char *file_token);
void			copy_args(char **src, char **dest);
char			**add_arg(char **cmd_args, char *arg);
void			fill_structs(t_shell *shell, char **tokens);

#endif