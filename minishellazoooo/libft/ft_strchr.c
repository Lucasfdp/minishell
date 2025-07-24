/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:56:30 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 01:58:37 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	a;

	i = 0;
	a = c;
	while (str[i] != '\0')
	{
		if (str[i] == a)
			return ((char *)(str + i));
		i++;
	}
	if (a == '\0')
		return ((char *)(str + i));
	return (NULL);
}

// int	main(void)
// {
// 	char	str[] = "A new string";
// 	char	c = '\0';

// 	char	*result = strchr(str, c);
// 	if (result != NULL)
// 	{
// 		printf("%c was found at the position %ld",c,  result - str);
// 	}
// 	else 
// 	printf("%c was not found in the string", c);
// 	return (0);
// }