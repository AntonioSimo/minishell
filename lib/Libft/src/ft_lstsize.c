/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 18:48:49 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/01 16:53:10 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

// int main(void)
// {

// 	t_list *a = ft_lstnew("Hello");
// 	t_list *b = ft_lstnew("Hello");
// 	t_list *c = ft_lstnew("Hello");
// 	t_list *d = ft_lstnew("Hello");
// 	t_list *e = ft_lstnew("Hello");

// 	a->next = b;
// 	b->next = c;
// 	c->next = d;
// 	d->next = e;
// 	e->next = NULL;
// 	printf("%d", ft_lstsize(a));
// }