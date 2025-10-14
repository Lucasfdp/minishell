#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_shell		t_shell;

typedef struct s_command	t_command;

//builtins
int		count_matrix(char **matrix);
void	execute_builtins(t_command *cmd, t_shell *shell);
void	execute_echo(char **args);
void	execute_pwd(void);
void	execute_env(char **envp_shell);
int		find_env_index(char **env, char *key);
char	*extract_key(char *var);
char	**append_to_env(char **env, char *new_var);
void	set_env_var(char ***env, char *new_var);
void	print_export(char **env);
void	execute_export(char **args, char ***env);
void	execute_unset(char **args, char ***env);
int		find_env_index(char **env, char *key);
char	**order_env(char **env);
void	execute_cd(char **args, char ***env);
char	*get_home(char **env);
char	*get_old_pwd(char **env);
void	execute_exit(char **args, t_shell *shell);

#endif
