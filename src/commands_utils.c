/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:19:31 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 16:14:31 by pskrucha         ###   ########.fr       */
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

t_command	*lst_cmd_new(char **args, t_redir *redir)
{
	t_command	*new_node;

	new_node = ptr_check(malloc(sizeof(t_command)));
	if (args)
	{
		new_node->arguments = push_str_2d(args, NULL);
		new_node->command = ptr_check(ft_strdup(new_node->arguments[0]));
	}
	else
	{
		new_node->arguments = push_str_2d(args, "");
		new_node->command = ft_strdup("");
	}
	new_node->redirections = redir;
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
	int	i;

	i = 0;
	while (cmd_lst)
	{
		printf("'cmd: %s'\n", cmd_lst->command);
		if (cmd_lst->arguments)
		{
			while (cmd_lst->arguments[i])
			{
				printf("'args: %s'\n", cmd_lst->arguments[i]);
				i++;
			}
		}
		i = 0;
		if (cmd_lst->redirections)
		{
			print_redirections(cmd_lst->redirections->lst);
		}
		cmd_lst = cmd_lst->next;
	}
}

void	*destroy_cmds(t_command	*cmd_lst)
{
	int			i;
	t_command	*node;

	i = 0;
	if (!cmd_lst)
		return (NULL);
	while (cmd_lst)
	{
		node = (cmd_lst)->next;
		// printf("here\n");
		while ((cmd_lst)->arguments[i])
		{
			free((cmd_lst)->arguments[i]);
			i++;
		}
		i = 0;
		free(cmd_lst->arguments);
		free(cmd_lst->command);
		cmd_lst->redirections = destroy_redir(cmd_lst->redirections);
		free(cmd_lst);
		cmd_lst = node;
	}
	return (NULL);
}
