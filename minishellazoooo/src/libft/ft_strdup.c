/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:03:51 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/07 01:58:51 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*new;

	len = ft_strlen(s) + 1;
	new = malloc(len);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// int	main(void)
// {
// 	char	*original_str = "General Kenobi";
// 	char	*new_str = ft_strdup(original_str);

// 	if (new_str == NULL)
// 	{
// 		printf("Failed");
// 		return (1);
// 	}
// 	printf("Original: %s\n", original_str);
// 	printf("New: %s", new_str);
// 	free(new_str);
// 	return (0);
// }