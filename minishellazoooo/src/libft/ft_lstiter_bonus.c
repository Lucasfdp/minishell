/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:05:58 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/06 23:47:37 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (!lst || !f)
		return ;
	while (lst)
	{
		temp = lst->next;
		if (lst->content != NULL)
			f(lst->content);
		lst = temp;
	}
}

// void	ft_printlst(t_list *head)
// {
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// }

// char	*ft_toupperex(char *c)
// {
//     int i;
//    
//     i = 0;
//     while (c[i] != '\0')
// 	{
//         if (c[i] >= 'a' && c[i] <= 'z')
// 	    {
// 		    c[i] = c[i] - 32;
//     	}
//         i++;
//     }
// 	return (c);
// }

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
//  	ft_lstadd_back(&head, node2);
// 	ft_lstadd_front(&head, node1);
// 	int	size = ft_lstsize(head);
// 	printf("%d\n", size);
// 	t_list	*lstnode = ft_lstlast(head);
// 	if (lstnode)
// 	{
// 		printf("The last node is: %s\n", (char *)lstnode->content);
// 	}
// 	else
// 	{
// 		printf("No data");
// 	}
// 	printf("List before f:\n");
// 	ft_printlst(head);
//     ft_lstiter(node3, (void *)ft_toupperex);
// 	// if (head == node1)
// 	// {
// 	// 	head = node1->next;
// 	// }
//     // ft_lstdelone(node1, delete);
//     // ft_lstclear(&head, delete);
// 	printf("List after f:\n");
// 	ft_printlst(head);
// 	return(0);
// }
