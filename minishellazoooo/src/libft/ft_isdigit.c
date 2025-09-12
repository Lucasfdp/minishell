/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:41:27 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/06 23:41:06 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// int	main(void)
// {
// 	char	a;
// 	char	b;
// 	char	c;

// 	a = '9';
// 	b = '2';
// 	c = '3';
// 	printf("%d\n", ft_isdigit(a));
// 	printf("%d\n", ft_isdigit(b));
// 	printf("%d\n", ft_isdigit(c));
// 	return (0);
// }