/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:08:19 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 02:00:14 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last;
	int			i;
	char		a;

	last = NULL;
	i = 0;
	a = c;
	while (str[i] != '\0')
	{
		if (str[i] == a)
			last = &str[i];
		i++;
	}
	if (a == '\0')
		return ((char *)(str + i));
	return ((char *)last);
}

// int	main(void)
// {
// 	char	str[] = "How many a characters are there here ay g";
// 	char	c = 'g';

// 	char	*result = ft_strrchr(str, c);
// 	if (result != NULL)
// 	{
// 		printf("%c has been found in the position %ld", c, result - str);
// 	}
// 	else 
// 	printf("The character %c has not been found", c);
// 	return (0);
// }