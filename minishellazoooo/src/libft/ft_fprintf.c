/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:56:00 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/21 22:09:57 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_fpf(const char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, ("(null)"), 6);
		return (6);
	}
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	handle_specifier(char specifier, va_list args, int fd)
{
	if (specifier == 'c')
		return (ft_putchar_fd_pf(va_arg(args, int), fd));
	else if (specifier == 's')
		return (ft_putstr_fd_pf(va_arg(args, char *), fd));
	else if (specifier == 'i' || specifier == 'd')
		return (ft_putnbr_fd_pf(va_arg(args, int), fd));
	else if (specifier == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789", fd));
	else if (specifier == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789abcdef", fd));
	else if (specifier == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int),
				"0123456789ABCDEF", fd));
	else if (specifier == 'p')
		return (ft_put_ptr_fd(va_arg(args, void *), fd));
	else if (specifier == '%')
		return (ft_putchar_fd_pf('%', fd));
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list			args;
	int				count;
	int				i;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			count += handle_specifier(format[i], args, fd);
		}
		else
		{
			write(fd, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
