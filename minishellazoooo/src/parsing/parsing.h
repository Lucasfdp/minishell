#ifndef PARSING_H
#define PARSING_H

# include "minishell.h"

// typedef struct s_tokens
// {

// }	t_tokens;

int		count_tokens(char *input);
char	**tokeniser(char *input);

#endif