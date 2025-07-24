#include "libft.h"

int	ft_strlen_pf(const char *str)
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
int	handle_specifier(char specifier, va_list args)
{
	if (specifier == 'c')
		return (ft_putchar_fd_pf(va_arg(args, int), 1));
	else if (specifier == 's')
		return (ft_putstr_fd_pf(va_arg(args, char *), 1));
	else if (specifier == 'i' || specifier == 'd')
		return (ft_putnbr_fd_pf(va_arg(args, int), 1));
	else if (specifier == 'u')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), "0123456789", 1));
	else if (specifier == 'x')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), "0123456789abcdef", 1));
	else if (specifier == 'X')
		return (ft_putnbr_base_fd(va_arg(args, unsigned int), "0123456789ABCDEF", 1));
	else if (specifier == 'p')
		return (ft_put_ptr_fd(va_arg(args, void *), 1));
	else if (specifier == '%')
		return (ft_putchar_fd_pf('%', 1));
	return (0);
}

int	ft_printf(const char *format, ...)
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
			count += handle_specifier(format[i], args);
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
