#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void	execute_commands(t_shell *shell);
void	exec_all(t_shell *shell, pid_t *pids);
void	exec_single_command(t_shell *shell, pid_t pid, int i);
void	exec_child(t_shell *shell, t_command *cmd);
void	duppy(int fd_input, int fd_output);

#endif