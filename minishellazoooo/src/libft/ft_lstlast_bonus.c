/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:18:19 by luferna3          #+#    #+#             */
/*   Updated: 2025/01/29 17:22:12 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	return (temp);
}

// int main(void)
// {
// 	t_list  *head;
// 	t_list  *node1;
// 	t_list  *node2;
// 	t_list  *node3;

// 	head = NULL;
//  	node1 = ft_lstnew("This is node 1");
//  	node2 = ft_lstnew("This is node 2");
//  	node3 = ft_lstnew("This is node 3");
//  	ft_lstadd_front(&head, node3);
//  	ft_lstadd_front(&head, node2);
// 	ft_lstadd_front(&head, node1);
// 	int	size = ft_lstsize(head);
// 	printf("%d\n", size);
// 	t_list	*lstnode = ft_lstlast(head);
// 	if (lstnode)
// 	{
// 		printf("%s\n", (char *)lstnode->content);
// 	}
// 	else
// 	{
// 		printf("No data");
// 	}
// 	return(0);
//  }
