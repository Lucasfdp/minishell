/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:38:04 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/02 20:27:01 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

// int	main(void)
// {
// 	int	fd;
// 	char	str[] = "General Kenobi";
// 	char	str2[] = "General Grevious";

// 	fd = open("newlinefile.txt", O_WRONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error");
// 	}
// 	ft_putendl_fd(str, fd);
// 	ft_putendl_fd(str2, fd);
// 	close(fd);
// 	return(0);
// }