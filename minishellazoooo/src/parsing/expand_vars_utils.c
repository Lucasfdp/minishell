/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:55:35 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:55:36 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(s, buf);
	return (tmp);
}

char	*get_env_value(char **envp, const char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return ("");
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	**tokens_to_argv(t_token **tokens)
{
	int		i;
	int		count;
	char	**argv;

	i = 0;
	count = 0;
	while (tokens[count])
		count++;
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	while (tokens[i])
	{
		argv[i] = ft_strdup(tokens[i]->value);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*strjoin_char_free(char *str, char c)
{
	char	*tmp;

	tmp = ft_strjoin_char(str, c);
	free(str);
	return (tmp);
}
