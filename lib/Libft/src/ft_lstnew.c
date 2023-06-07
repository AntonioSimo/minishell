/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 10:50:26 by asimone       #+#    #+#                 */
/*   Updated: 2023/03/08 17:34:07 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

//void	print_node(t_list *new_node, char *comment)
//{
//	if (new_node == NULL)
//		printf ("%s is NULL\n", comment);
//	else
//		printf ("%s: content:%d address:%p next:%p\n", 
//		comment, new_node->content, new_node, new_node->next);
//}

//int main(void)
//{
//	t_list *a = NULL;
//	t_list *b = NULL;

//	print_node (a, "first");
//	print_node (b, "second");
//	a = ft_lstnew (100);
//	b = ft_lstnew (75);
//	print_node (a, "first");
//	print_node (b, "second");
//	a->next = b;
//	print_node (a, "first");
//	print_node (a->next, "first->next");
//	print_node (b, "second");
//	free (a);
//	free (b);
//	a = NULL;
//	b = NULL;
//	return (0);
//}