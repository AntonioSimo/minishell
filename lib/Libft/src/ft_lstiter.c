/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: asimone <asimone@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 16:08:32 by asimone       #+#    #+#                 */
/*   Updated: 2022/11/10 18:14:29 by asimone       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		f (lst->content);
		lst = lst->next;
	}
}

//void    ft_modify_list_with_d(void *elem)
//{
//        int             len;
//        char            *content;

//        len = 0;
//        content = (char *)elem;
//        while (content[len])
//        {
//                content[len++] = 'd';
//        }
//}

//void    ft_print_result(t_list *elem)
//{
//        int             len;

//        while (elem)
//        {
//                len = 0;
//                while (((char *)elem->content)[len])
//                        len++;
//                write(1, elem->content, len);
//                write(1, "\n", 1);
//                elem = elem->next;
//        }
//}

//t_list  *ft_lstnewone(void *content)
//{
//        t_list  *elem;

//        elem = (t_list *)malloc(sizeof(t_list));
//        if (!elem)
//                return (NULL);
//        if (!content)
//                elem->content = NULL;
//        else
//                elem->content = content;
//        elem->next = NULL;
//        return (elem);
//}

//int main(int argc, const char *argv[])
//{
//        t_list          *elem;
//        t_list          *elem2;
//        t_list          *elem3;
//        t_list          *elem4;
//        char            *str = strdup("lorem");
//        char            *str2 = strdup("ipsum");
//        char            *str3 = strdup("dolor");
//        char            *str4 = strdup("sit");

//        elem = ft_lstnewone(str);
//        elem2 = ft_lstnewone(str2);
//        elem3 = ft_lstnewone(str3);
//        elem4 = ft_lstnewone(str4);
//        alarm(TIMEOUT);
//        if (argc == 1 || !elem || !elem2 || !elem3 || !elem4)
//                return (0);
//        elem->next = elem2;
//        elem2->next = elem3;
//        elem3->next = elem4;
//        if (atoi(argv[1]) == 1)
//        {
//                ft_lstiter(elem, &ft_modify_list_with_d);
//                ft_print_result(elem);
//        }
//        return (0);
//}