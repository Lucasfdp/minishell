/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:14:03 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 01:59:01 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f) (unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

// static void	ft_ex_func(unsigned int i, char *c)
// {
// 	if (i % 2 == 0)
// 	{
// 		*c = ft_toupper(*c);
// 	}
// 	else
// 	{
// 		*c = ft_tolower(*c);
// 	}
// }

// int	main(void)
// {
// 	char	str[] = "General Kenobi";
// 	ft_striteri(str, ft_ex_func);
// 	printf("%s", str);
// 	return (0);
// }