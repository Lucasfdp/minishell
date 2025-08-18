/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:02:34 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/02 21:17:31 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		to_find;
	size_t				i;

	ptr = s;
	to_find = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == to_find)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const unsigned char	str[] = "How uncivilised";
// 	unsigned char	c = 'd';
// 	unsigned int	n = 20;

// 	unsigned char	*result = memchr(str, c, n);
// 	if (result)
// 	{
// 		printf("Found %c at position %ld\n", c, result - str);
// 	}
// 	else 
// 	printf("Character %c not found", c);
// 	return (0);
// }