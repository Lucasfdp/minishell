/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:50:21 by luferna3          #+#    #+#             */
/*   Updated: 2025/03/06 23:41:47 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	del(lst->content);
	free(lst);
}

// void	delete(void *node)
// {
// 	free(node);
// }

// void	ft_printlst(t_list *head)
// {
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
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
// 		printf("%s\n", (char *)lstnode->content);
// 	}
// 	else
// 	{
// 		printf("No data");
// 	}
// 	printf("List before del:\n");
// 	ft_printlst(head);
// 	if (head == node1)
// 	{
// 		head = node1->next;
// 	}
//     ft_lstdelone(node1, delete);
// 	printf("List after del:\n");
// 	ft_printlst(head);
// 	return(0);
// }
// int main()
// {
//     Creating three integers to be stored in the list
//     int *data1 = (int *)malloc(sizeof(int));
//     *data1 = 42;
//     int *data2 = (int *)malloc(sizeof(int));
//     *data2 = 84;
//     int *data3 = (int *)malloc(sizeof(int));
//     *data3 = 168;

//     Check for malloc failure
//     if (!data1 || !data2 || !data3)
//     {
//         printf("Memory allocation failed.\n");
//         return 1;  // Exit if memory allocation fails
//     }

//     Creating three list nodes
//     t_list *node1 = ft_lstnew(data1);
//     t_list *node2 = ft_lstnew(data2);
//     t_list *node3 = ft_lstnew(data3);

//     Check if list node creation failed
//     if (!node1 || !node2 || !node3)
//     {
//         printf("Memory allocation for list nodes failed.\n");
//         return 1;
//     }

//     Linking the nodes together
//     node1->next = node2;
//     node2->next = node3;

//     Print the list before deletion
//     printf("List before deletion:\n");
//     ft_printlst(node1);

//     Now, delete the second node (node2) and its content
//     First, update node1->next to point to node3
//     node1->next = node2->next;

//     Delete the second node
//     ft_lstdelone(node2, delete);

//     Print the list after deletion
//     printf("\nList after deletion of second node:\n");
//     ft_printlst(node1);

//     Delete the first node
//     ft_lstdelone(node1, delete);

//     Delete the third node
//     ft_lstdelone(node3, delete);

//     return 0;
// }