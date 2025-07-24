/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:31:53 by luferna3          #+#    #+#             */
/*   Updated: 2025/05/26 02:33:16 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_putchar_fd_pf(char c, int fd)
{
    write(fd, &c, 1);
    return (1);
}

int ft_putstr_fd_pf(char  *str, int fd)
{
    write(fd, str, ft_strlen_pf(str));
    return (ft_strlen_pf(str));
}

int ft_putnbr_fd_pf(int nbr, int fd)
{
    int count;

    count = 0;
    if (nbr < 0)
    {
        if (nbr == INT_MIN)
            count += ft_putstr_fd_pf("-2147483648", fd);
        else
            nbr = -nbr;
    }
    if (nbr >= 10)
        count += ft_putnbr_fd_pf(nbr / 10, fd);
    count += ft_putchar_fd_pf(((nbr % 10) + '0'), fd);
    return (count);
}

int ft_putnbr_base_fd(unsigned long nbr, char *base, int fd)
{
    int count;

    count = 0;
    if (nbr >= (unsigned long)ft_strlen_pf(base))
        count += ft_putnbr_base_fd(nbr / ft_strlen_pf(base), base, fd);
    nbr = nbr % ft_strlen_pf(base);
    count += ft_putchar_fd_pf(base[nbr], fd);
    return (count);
}

int ft_put_ptr_fd(void *ptr, int fd)
{
    if (!ptr)
        return (ft_putstr_fd_pf("(nil)", fd));
    ft_putstr_fd_pf("0x", fd);
    return (ft_putnbr_base_fd((unsigned long)ptr, "0123456789abcdef", fd) + 2);
}
