/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 11:03:43 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/01 16:52:48 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int main(void)
// {
// 	t_list *a = ft_lstnew("Ciao");
// 	t_list *b = ft_lstnew("mi");
// 	t_list *c = ft_lstnew("chiamo");
// 	t_list *d = ft_lstnew("Antonio");
// 	t_list *e = ft_lstnew("Simone");

// 	a->next = b;
// 	b->next = c;
// 	c->next = d;
// 	d->next = e;
// 	e->next = NULL;
// 	printf("%s", ft_lstlast(a)->content);
// }