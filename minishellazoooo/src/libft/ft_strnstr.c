/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:02:38 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/02 21:22:59 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	if (*little == '\0')
		return ((char *)big);
	x = 0;
	while (big[x] != '\0' && x < len)
	{
		if (big[x] == little[0])
		{
			y = 0;
			while (big[x + y] == little[y] && little[y] != '\0'
				&& (x + y) < len)
				y++;
			if (little[y] == '\0')
				return ((char *)(big + x));
		}
		x++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	big[] = "abcdefghijklmnop";
// 	char	little[] = "fgh";
// 	unsigned int	len = 8;
// 	char	*string = ft_strnstr(big, little, len);

// 	if (string)
// 	{
// 		printf("%s", string);
// 	}
// 	else 
// 	printf("No string found");
// 	return (0);
// }