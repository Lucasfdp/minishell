/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:23:42 by luferna3          #+#    #+#             */
/*   Updated: 2025/05/26 02:30:44 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	i = 0;
	if (size <= destlen)
		return (size + srclen);
	while (src[i] != '\0' && destlen + i < size - 1)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}



// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	a;
// 	int		i;

// 	a = 0;
// 	i = 0;
// 	while (dst[a] != '\0')
// 		a++;
// 	if (size > a)
// 		size = (size - a) - 1;
// 	else
// 		return (size + ft_strlen(src));
// 	while (size > 0 && src[i] != '\0')
// 	{
// 		dst[a] = src[i];
// 		a++;
// 		i++;
// 		size--;
// 	}
// 	dst[a] = '\0';
// 	return (ft_strlen(dst) + ft_strlen(src) - i);
// }

// int	main(void)
// {
// 	char	dest[50] = "These are not the droids you are looking for ";
// 	char	src[] = "My name jeff";

// 	char	number = ft_strlcat(dest, src, 100);

// 	printf("String is: %s\n", dest);
// 	printf("String length is: %d", number);
// 	return (0);
// }