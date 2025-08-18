/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:46:48 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 01:59:48 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			str_len;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	str_len = ft_strlen(s);
	result = malloc(str_len + 1 * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

// static char	ft_ex_func(unsigned int i, char c)
// {
// 	if (i % 2 == 0)
// 	{
// 		return (ft_tolower(c));
// 	}
// 	return (ft_toupper(c));
// }

// int	main(void)
// {
// 	char	str[] = "General Kenobi";
// 	char	*result = ft_strmapi(str, ft_ex_func);

// 	if (result)
// 	{
// 		printf("The original string: %s\n", str);
// 		printf("The string after applying function: %s", result);
// 		free(result);
// 	}
// 	return (0);
// }