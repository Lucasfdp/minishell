#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_shell		t_shell;

typedef struct s_command	t_command;

void	execute_commands(t_shell *shell);
void	exec_all(t_shell *shell, pid_t *pids);
void	exec_single_command(t_shell *shell, pid_t pid, int i);
void	exec_child(t_shell *shell, t_command *cmd);
void	duppy(int fd_input, int fd_output);
void	apply_redirs(t_command *cmd);

void	setup_pipes(t_shell *shell);
int		detect_builtin(char *str);
void	close_all_pipes(t_shell *shell);

char	*get_path_from_env(char **envp);
char	*try_paths(char **split_paths, char *cmd);
char	*get_cmd_path(t_shell *shell, t_command *cmd);
int		ft_lstsize_2(t_command *lst);
int	open_file_safe(char *file, int flags, int mode);
void	dup_and_close(int fd, int target_fd);

#endif