/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:19:31 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/06 14:54:32 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_command	*lst_cmd_last(t_command *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_command	*lst_cmd_new(char **args)
{
	t_command	*new_node;

	new_node = ptr_check(malloc(sizeof(t_command)));
	new_node->arguments = ptr_check(push_str_2d(args, NULL));
	new_node->command = ptr_check(ft_strdup(new_node->arguments[0]));
	new_node->next = NULL;
	return (new_node);
}

void	push_cmd(t_command **lst, t_command *new)
{
	t_command	*lst_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_node = lst_cmd_last(*lst);
	lst_node->next = new;
}

void	print_cmds(t_command *cmd_lst)
{
    int i;

    i = 0;
	while (cmd_lst)
    {
        printf("'cmd: %s'\n", cmd_lst->command);
        while (cmd_lst->arguments[i])
        {
            printf("'args: %s'\n", cmd_lst->arguments[i]);
            i++;
        }
        i = 0;
        printf("\n");
        cmd_lst = cmd_lst->next;
    }
}

void	*destroy_cmds(t_command	*cmd_lst)
{
    int i; //this function needs to be finished to free everything

    i = 0;
	if (!cmd_lst)
		return (NULL);
	while (cmd_lst)
	{
        while (cmd_lst->arguments[i])
        {
            ft_free(cmd_lst->arguments[i]);
            i++;
        }
        i = 0;
		ft_free(cmd_lst->command);
		cmd_lst = cmd_lst->next;
	}
	return (NULL);
}
