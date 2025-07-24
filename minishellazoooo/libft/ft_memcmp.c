/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:36:23 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/02 20:26:05 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = s1;
	ptr2 = s2;
	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			return (ptr1[i] - ptr2[i]);
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const unsigned char	str1[] = "general";
// 	const unsigned char	str2[] = "General";
// 	size_t	n = 8;

// 	int	result = ft_memcmp(str1, str2, n);
// 	if (result == 0)
// 	{
// 		printf("They are the same");
// 	}

// 	else if (result > 0)
// 	{
// 		printf("1 is greater than 2");
// 	}
// 	else
// 	{
// 		printf("2 is greater than 1");
// 	}
// 	return (0);
// }