/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:39:42 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 01:57:59 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			n = 147483648;
		}
		else
			n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

// int	main(void)
// {
// 	int	fd;
// 	int	num;

// 	num = -2147483648;
// 	fd = open("nbrfile.txt", O_WRONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error");
// 	}
// 	ft_putnbr_fd(num, fd);
// 	close(fd);
// 	return (0);
// }