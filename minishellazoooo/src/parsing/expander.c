/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:55:23 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 21:55:24 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand_backslash(char *token, int i, char **result, int in_double)
{
	i++;
	if (token[i])
	{
		if (!in_double || token[i] == '$' || token[i] == '"'
			|| token[i] == '\\' || token[i] == '`')
			*result = strjoin_char_free(*result, token[i]);
		else
			*result = strjoin_char_free(*result, '\\');
		i++;
	}
	return (i);
}

int	expand_exit_status(t_shell *shell, char **result)
{
	char	*code;

	code = ft_itoa(shell->exit_status);
	*result = strjoin_free(*result, code);
	free(code);
	return (1);
}

int	expand_env_var(char *token, int i, char **result, t_shell *shell)
{
	int		start;
	char	*var_name;
	char	*val;

	start = i;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	var_name = ft_substr(token, start, i - start);
	val = get_env_value(shell->env, var_name);
	*result = strjoin_free(*result, val);
	free(var_name);
	return (i);
}

int	expand_dollar(t_shell *shell, char *token, int i, char **result)
{
	i++;
	if (token[i] == '?')
		return (i + expand_exit_status(shell, result));
	else if (ft_isalpha(token[i]) || token[i] == '_')
		return (expand_env_var(token, i, result, shell));
	else
	{
		*result = strjoin_char_free(*result, '$');
		return (i);
	}
}

char	*expand_variables(t_shell *shell, char *token, int in_double)
{
	char	*result;
	int		i;

	result = ft_calloc(1, 1);
	i = 0;
	while (token[i])
	{
		if (token[i] == '\\')
			i = expand_backslash(token, i, &result, in_double);
		else if (token[i] == '$')
			i = expand_dollar(shell, token, i, &result);
		else
		{
			result = strjoin_char_free(result, token[i]);
			i++;
		}
	}
	return (result);
}
