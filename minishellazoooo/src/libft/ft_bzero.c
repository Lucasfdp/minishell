/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 18:28:51 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/03 13:17:14 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int	main(void)
// {
// 	char	str[] = "String";
// 	unsigned int	n = 1;

//  	printf("%s\n", str);
//  	ft_bzero(str, n);
//  	printf("Should be blank: %s", str);
// 	return (0);
// }