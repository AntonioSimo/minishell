/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 11:39:21 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/01 16:45:43 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main(void)
// {
// 	t_list *old_start = ft_lstnew("it works");
// 	t_list *new_start = ft_lstnew("new start");
// 	t_list *node1 = ft_lstnew("it doesn't");

// 	old_start->next = node1;
// 	node1->next = NULL;
// 	ft_lstadd_front(&old_start, new_start);
// 	printf("%s", new_start->next->content);
// }
