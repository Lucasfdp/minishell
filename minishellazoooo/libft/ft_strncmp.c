/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:41:19 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 01:59:59 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

// int	main(void)
// {
// 	char	str1[] = "This is going to be the same";
// 	char	str2[] = "This is going to be the same";
// 	char	str3[] = "This is going to be different";
// 	char	str4[] = "This is going to be hididifkv";

// 	ft_strncmp(str1, str2, 5);
// 	ft_strncmp(str3, str4, 5);
// 	printf("%d\n", ft_strncmp(str1, str2, 28));
// 	printf("%d\n", ft_strncmp(str3, str4, 32));
// 	int	result = ft_strncmp("abcdef", "abc\375xx", 5);
// 	printf("%d\n", result);
// 	int	result2 = ft_strncmp("test\200", "test\0", 6);
// 	printf("%d", result2);
// 	return (0);
// }