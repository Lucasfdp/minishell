#include "minishell.h"

char *ft_strjoin_char(char *s, char c)
{
    char buf[2];
	char *tmp;
	
    buf[0] = c;
    buf[1] = '\0';
    tmp = ft_strjoin(s, buf);
    return tmp;
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

int	count_tokens(char *input)
{
	int i = 0;
	int count = 0;
	int in_single = 0;
	int in_double = 0;

	while (input[i])
	{
		// Skip spaces
		while (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break;

		// Operator tokens (|, <, >, <<, >>)
		if (!in_single && !in_double && is_operator_char(input[i]))
		{
			count++;
			if ((input[i] == '<' && input[i + 1] == '<')
				|| (input[i] == '>' && input[i + 1] == '>'))
				i += 2;
			else
				i++;
			continue;
		}

		// Word or quoted token
		count++;
		while (input[i] && (!ft_isspace(input[i]) || in_single || in_double))
		{
			if (input[i] == '\'' && !in_double)
				in_single = !in_single;
			else if (input[i] == '"' && !in_single)
				in_double = !in_double;
			else if (!in_single && !in_double && is_operator_char(input[i]))
				break;
			i++;
		}
	}

	return (count);
}


t_token **tokeniser(char *input)
{
    int i = 0, j = 0, k = 0;
    int single_q = 0, double_q = 0;
    int num_tokens = count_tokens(input);
    char *buf = malloc(ft_int_strlen(input) + 1);
    t_token **tokens = malloc(sizeof(t_token *) * (num_tokens + 1));
    char op[3];

    if (!tokens || !buf)
        return (NULL);

    while (input[i])
    {
        while (ft_isspace(input[i]))
            i++;
        if (!input[i])
            break;

        k = 0;
        single_q = 0;
        double_q = 0;

        // Check operators first
        if (is_operator_char(input[i]) && !single_q && !double_q)
        {
            if (input[i] == '<' && input[i + 1] == '<')
            {
                ft_strlcpy(op, "<<", 3);
                i += 2;
            }
            else if (input[i] == '>' && input[i + 1] == '>')
            {
                ft_strlcpy(op, ">>", 3);
                i += 2;
            }
            else
            {
                op[0] = input[i++];
                op[1] = '\0';
            }

            tokens[j] = malloc(sizeof(t_token));
            tokens[j]->value = ft_strdup(op);
            tokens[j]->in_single = 0;
            tokens[j]->in_double = 0;
            j++;
            continue;
        }

        int starts_with_single = (input[i] == '\'');
        int starts_with_double = (input[i] == '"');

        while (input[i] && (!ft_isspace(input[i]) || single_q || double_q))
        {
            if (input[i] == '\\')
            {
                i++;
                if (input[i])
                {
                    // In double quotes, only certain chars are escaped
                    if (!double_q || input[i] == '$' || input[i] == '"' || input[i] == '\\' || input[i] == '`')
                        buf[k++] = input[i];
                    else
                        buf[k++] = '\\';
                    i++;
                }
            }
            else if (input[i] == '\'' && !double_q)
            {
                single_q = !single_q;
                i++;
            }
            else if (input[i] == '"' && !single_q)
            {
                double_q = !double_q;
                i++;
            }
            else if (!single_q && !double_q && is_operator_char(input[i]))
                break;
            else
                buf[k++] = input[i++];
        }

        buf[k] = '\0';
        tokens[j] = malloc(sizeof(t_token));
        tokens[j]->value = ft_strdup(buf);
        tokens[j]->in_single = starts_with_single;
        tokens[j]->in_double = starts_with_double;
        j++;
    }

    tokens[j] = NULL;
    free(buf);

    if (single_q || double_q)
    {
        ft_fprintf(STDERR_FILENO, "bash: -c: line 0: unexpected EOF while looking for matching `''\n");
        ft_fprintf(STDERR_FILENO, "bash: -c: line 1: syntax error: unexpected end of file\n");
        return (NULL);
    }

    return tokens;
}

char **tokens_to_argv(t_token **tokens)
{
    int i = 0;
    int count = 0;
    char **argv;

    // Count tokens
    while (tokens[count])
        count++;

    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);

    // Duplicate token values
    while (tokens[i])
    {
        argv[i] = ft_strdup(tokens[i]->value);
        i++;
    }
    argv[i] = NULL;

    return (argv);
}

char *expand_variables(t_shell *shell, char *token, int in_double)
{
    char *result = ft_calloc(1, 1);
    char *tmp;
    char *code;
    char *val;
    char *var_name;
    int start;
    int i = 0;

    while (token[i])
    {
        if (token[i] == '\\')
        {
            i++;
            if (token[i])
            {
                // Only escape special chars in double quotes
                if (!in_double || token[i] == '$' || token[i] == '"' || token[i] == '\\' || token[i] == '`')
                    tmp = ft_strjoin_char(result, token[i]);
                else
                    tmp = ft_strjoin_char(result, '\\');
                free(result);
                result = tmp;
                i++;
            }
        }
        else if (token[i] == '$')
        {
            i++;
            if (token[i] == '?')
            {
                code = ft_itoa(shell->exit_status);
                tmp = ft_strjoin(result, code);
                free(result);
                free(code);
                result = tmp;
                i++;
            }
            else if (ft_isalpha(token[i]) || token[i] == '_')
            {
                start = i;
                while (ft_isalnum(token[i]) || token[i] == '_')
                    i++;
                var_name = ft_substr(token, start, i - start);
                val = get_env_value(shell->env, var_name);
                tmp = ft_strjoin(result, val);
                free(result);
                free(var_name);
                result = tmp;
            }
            else
            {
                tmp = ft_strjoin_char(result, '$');
                free(result);
                result = tmp;
            }
        }
        else
        {
            tmp = ft_strjoin_char(result, token[i]);
            free(result);
            result = tmp;
            i++;
        }
    }
    return (result);
}

// Expand all tokens after tokenization
void expand_tokens(t_shell *shell, t_token **tokens)
{
    int i = 0;
    char *expanded;

    while (tokens[i])
    {
        if (!tokens[i]->in_single) // skip single-quoted
        {
            expanded = expand_variables(shell, tokens[i]->value, tokens[i]->in_double);
            free(tokens[i]->value);
            tokens[i]->value = expanded;
        }
        i++;
    }
}
