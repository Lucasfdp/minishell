/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 01:55:58 by luferna3          #+#    #+#             */
/*   Updated: 2025/05/27 02:06:18 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int main(int ac, char *av[])
// {
//     (void)ac;
//     ft_printf("hola, %s", av[1]);
//     return 0;
// }

int main(void)
{
    int fd = open("ex.txt", O_RDONLY);
    char *line = NULL;

    while ((line = get_next_line(fd)) != NULL)
    {
        ft_printf("Line: %s\n", line);
        free(line);
    }

    close(fd);
    return (0);
}