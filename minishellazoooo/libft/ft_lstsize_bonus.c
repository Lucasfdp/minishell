/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:50:00 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/02 20:25:32 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*temp;

	count = 0;
	temp = lst;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

// int main(void)
// {
//  	t_list  *head;
//  	t_list  *node1;
//  	t_list  *node2;
//  	t_list  *node3;

//  	head = NULL;
//  	node1 = ft_lstnew("This is node 1");
//  	node2 = ft_lstnew("This is node 2");
//  	node3 = ft_lstnew("This is node 3");
//  	ft_lstadd_front(&head, node1);
//  	ft_lstadd_front(&head, node2);
// 	ft_lstadd_front(&head, node3);
// 	int	size = ft_lstsize(head);
// 	printf("%d", size);
// 	return(0);
//  }