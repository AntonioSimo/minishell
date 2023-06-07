/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 11:35:49 by asimone       #+#    #+#                 */
/*   Updated: 2023/03/06 12:17:02 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_node = ft_lstlast(*lst);
	lst_node->next = new;
}

// int main(void)
// {
// 	t_list *a = ft_lstnew("Ciao");
// 	t_list *b = ft_lstnew("sono");
// 	t_list *c = ft_lstnew("Antonio");

// 	b->next = c;
// 	c->next = a;
// 	a->next = NULL;
// 	printf("%s", c->next->content);
// }