/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:58:41 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/06 23:41:19 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_nums(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static int	ft_abval(int n)
{
	if (n < 0)
	{
		return (-n);
	}
	return (n);
}

static char	*ft_convertnum(int len, int n, char *result)
{
	int	is_neg;

	is_neg = (n < 0);
	while (len > 0)
	{
		len--;
		result[len] = ft_abval(n % 10) + '0';
		n = n / 10;
	}
	if (is_neg)
	{
		result[0] = '-';
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	if (n == 0)
	{
		result = malloc (2 * sizeof(char));
		if (!result)
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	len = ft_count_nums(n);
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_convertnum(len, n, result);
	result[len] = '\0';
	return (result);
}

// int	main(void)
// {
// //	int	n = 1000034;

// 	char	*result = ft_itoa(-637374);
// 	printf("The number converted is: %s", result);
// 	free(result);
// 	return (0);
// }