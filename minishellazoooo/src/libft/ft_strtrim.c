/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:47:34 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 02:00:19 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_inset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	start = 0;
	while (*s1 && ft_inset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_inset(s1[end - 1], set))
		end--;
	trimmed = malloc((end - start + 1) * sizeof(char));
	if (!trimmed)
	{
		return (NULL);
	}
	i = 0;
	while (end > start)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}

// int	main(void)
// {
// 	char	*str = "cababacagGeneralcabacab";
// 	char	*set = "abcg";
// 	char	*result = ft_strtrim(str, set);

// 	if (result)
// 	{
// 		printf("Trimmed string is: %s", result);
// 	}
// 	free(result);
// 	return (0);
// }