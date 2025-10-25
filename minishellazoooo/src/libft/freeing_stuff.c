/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:55:51 by luferna3          #+#    #+#             */
/*   Updated: 2025/10/25 05:32:43 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_map(char **map, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_int_array(int **array, int count)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
