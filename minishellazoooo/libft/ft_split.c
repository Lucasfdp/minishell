/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:21:53 by luferna3          #+#    #+#             */
/*   Updated: 2025/05/27 02:51:13 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_subs(const char *s, char c)
{
	size_t	num_subs;

	num_subs = 0;
	while (*s)
	{
		if (*s != c)
		{
			num_subs++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (num_subs);
}

void	ft_free_all(char **result, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (result[i])
			free(result[i]);
		i++;
	}
	free(result);
}

char	**dosplit(const char *s, char c, char **result)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			result[i] = ft_substr(s - len, 0, len);
			if (!result)
			{
				ft_free_all(result, i);
				return (0);
			}
			i++;
		}
		else
			s++;
	}
	result[i] = 0;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	result = malloc(sizeof(char *) * (ft_count_subs(s, c) + 1));
	if (!result)
		return (0);
	result = dosplit(s, c, result);
	return (result);
}

// int	main(void)
// {
// 	char	str[] = "hello!";
// 	char	c = ' ';
// 	char	**result = ft_split(str, c);
// 	int	i;

// 	i = 0;
// 	if (result)
// 	{
// 		while (result[i])
// 		{
// 			printf("Substring %d is: %s\n", i, result[i]);
// 			free(result[i]);
// 			i++;
// 		}
// 		free(result);
// 	}
// 	return (0);
// }
