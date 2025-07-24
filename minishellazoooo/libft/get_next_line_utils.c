/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:12:10 by luferna3          #+#    #+#             */
/*   Updated: 2025/05/27 02:52:09 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// void	*ft_calloc(size_t count, size_t size)
// {
// 	char	*ptr;
// 	size_t	i;

// 	i = 0;
// 	ptr = malloc(count * size);
// 	if (!ptr)
// 		return (NULL);
// 	while (i < count * size)
// 	{
// 		ptr[i] = 0;
// 		i++;
// 	}
// 	return (ptr);
// }

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*joint_str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	joint_str = ft_calloc(sizeof(char), ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!joint_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		joint_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		joint_str[i + j] = s2[j];
		j++;
	}
	free(s1);
	return (joint_str);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int		i;
	char	a;

	i = 0;
	a = c;
	while (str[i] != '\0')
	{
		if (str[i] == a)
		{
			return ((char *)(str + i));
		}
		i++;
	}
	if (a == '\0')
	{
		return ((char *)(str + i));
	}
	return (NULL);
}

char	*ft_substr_gnl(char *s, int start, int len)
{
	char	*dst;
	int		i;

	if ((!s) || (start > ft_strlen_gnl(s)))
		return (NULL);
	if (len > (ft_strlen_gnl(s) - start))
		len = ft_strlen_gnl(s) - start;
	dst = ft_calloc(sizeof(char), len + 2);
	if (!dst)
		return (NULL);
	i = 0;
	while (len >= i)
	{
		dst[i] = s[start + i];
		i++;
	}
	return (dst);
}
