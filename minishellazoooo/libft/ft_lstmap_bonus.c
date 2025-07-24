/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luferna3 <luferna3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:03:48 by luferna3          #+#    #+#             */
/*   Updated: 2025/02/04 20:21:51 by luferna3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;
	void	*test;

	newlist = NULL;
	if (!lst || !f || !del)
		return (NULL);
	if (!lst->content)
	{
		ft_lstclear(&newlist, del);
		return (NULL);
	}
	while (lst)
	{
		test = f(lst->content);
		newnode = ft_lstnew(test);
		if (!newnode)
		{
			ft_lstdelone(newnode, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
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

// void	delete(void *node)
// {
// 	free(node);
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
//  	node3 = ft_lstnew("void	ft_printlst(t_list *head)
// {
// 	while (head)
// 	{
// 		printf("%s\n", (char *)head->content);
// 		head = head->next;
// 	}
// }

// void	*ft_toupperex(void *c)
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

// void	delete(void *node)
// {
// 	free(node);
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
// 	{// Allocating memory for transformed content
// 		printf("No data");void *transform(void *content) {
//     char *str = (char *)content;
//     size_t len = ft_strlen(str);
//     char *new_str = malloc(len + 1);
//     if (new_str)
//         ft_memcpy(new_str, str, len + 1);  // Copying string content
//     return new_str;
// }

// void del(void *content) {
//     free(content);
// }

// int main() {
//     // Create a test linked list
//     t_list *lst = NULL;
//     char *str1 = ft_strdup("hello");
//     char *str2 = ft_strdup("world");
//     char *str3 = ft_strdup("test");

//     ft_lstadd_back(&lst, ft_lstnew(str1));
//     ft_lstadd_back(&lst, ft_lstnew(str2));
//     ft_lstadd_back(&lst, ft_lstnew(str3));

//     // Apply ft_lstmap with transformation function and del function
//     t_list *new_list = ft_lstmap(lst, transform, del);

//     // Print results to verify output
//     t_list *tmp = new_list;
//     while (tmp) {
//         printf("Mapped content: %s\n", (char *)tmp->content);
//         tmp = tmp->next;
//     }

//     // Clean up the lists
//     ft_lstclear(&lst, del);
//     ft_lstclear(&new_list, del);

//     return 0;
// }
// 	}
// 	printf("List before f:\n");
// 	ft_printlst(head);
//     ft_lstmap(node1, ft_toupperex, delete);
// 	// if (head == node1)
// 	// {
// 	// 	head = node1->next;
// 	// }
//     // ft_lstdelone(node1, delete);
//     // ft_lstclear(&head, delete);
// 	printf("List after f:\n");
// 	ft_printlst(head);
// 	return(0);
// }This is node 3");
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
//     ft_lstmap(node1, ft_toupperex, delete);
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

// void *transform(void *content) {
//     char *str = (char *)content;
//     size_t len = ft_strlen(str);
//     char *new_str = malloc(len + 1);
//     if (new_str)
//         ft_memcpy(new_str, str, len + 1);  // Copying string content
//     return new_str;
// }
// void *transform(void *content) {
//     char *str = (char *)content;
//     size_t len = ft_strlen(str);
//     char *new_str = malloc(len + 1);
//     if (new_str)
//         ft_memcpy(new_str, str, len + 1);  // Copying string content
//     return new_str;
// }

// void del(void *content) {
//     free(content);
// }

// void del(void *content) {
//     free(content);
// }

// int main() {
//     // Create a test linked list
//     t_list *lst = NULL;
//     char *str1 = ft_strdup("hello");
//     char *str2 = ft_strdup("world");
//     char *str3 = ft_strdup("test");

//     ft_lstadd_back(&lst, ft_lstnew(str1));
//     ft_lstadd_back(&lst, ft_lstnew(str2));
//     ft_lstadd_back(&lst, ft_lstnew(str3));

//     // Apply ft_lstmap with transformation function and del function
//     t_list *new_list = ft_lstmap(lst, transform, del);

//     // Print results to verify output
//     t_list *tmp = new_list;
//     while (tmp) {
//         printf("Mapped content: %s\n", (char *)tmp->content);
//         tmp = tmp->next;
//     }

//     // Clean up the lists
//     ft_lstclear(&lst, del);
//     ft_lstclear(&new_list, del);

//     return 0;
// }
