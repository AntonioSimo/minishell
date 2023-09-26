/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:19:31 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/26 18:59:04 by pskrucha         ###   ########.fr       */
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

void	print_redirections(t_redir	*redir)
{
	const char	*type_str[] = {
	[REDIR_INPUT] = "REDIR_INPUT",
	[HEREDOC] = "HEREDOC",
	[REDIR_OUTPUT] = "REDIR_OUTPUT",
	[REDIR_OUTPUT_APPEND] = "REDIR_OUTPUT_APPEND",
	};
	while (redir)
	{
		printf("type = %-12s | str = '%s'\n", \
		type_str[redir->type], redir->file);
		redir = redir->next;
	}
}

int redir_size(t_redir	*redir)
{
	int i=0;
	if (!redir)
		return(0);
	while (redir)
	{
		i++;
		redir = redir->next;
	}
	return (i);
}

void	print_cmds(t_command *cmd_lst)
{
    int i;

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
		print_redirections(cmd_lst->redirections);
        cmd_lst = cmd_lst->next;
    }
}

void	*destroy_cmds(t_command	*cmd_lst)
{
    int i; //this function needs to be finished to free everything
	t_command	*node;
    i = 0;
	if (!cmd_lst)
		return (NULL);
	while (cmd_lst)
	{
		node = (cmd_lst)->next;
        while ((cmd_lst)->arguments[i])
        {
            ft_free((cmd_lst)->arguments[i]);
            i++;
        }
        i = 0;
		destroy_redir(cmd_lst->redirections);
		free((cmd_lst)->command);
		cmd_lst = node;
	}
	return (NULL);
}

t_redir	*lst_redir_new(char	*file, t_type type)
{
	t_redir *redir;

	redir = ptr_check(malloc(sizeof(t_redir)));
	redir->file = ptr_check(ft_strdup(file));
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_redir	*redir_lst_last(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	push_redir(t_redir **redir_lst, t_redir *redir)
{
	t_redir	*redir_node;
	
	if (*redir_lst == NULL)
	{
		*redir_lst = redir;
		return ;
	}
	redir_node = redir_lst_last(*redir_lst);
	redir_node->next = redir;
}

void	*destroy_redir(t_redir *redir)
{
	t_redir	*node;
	
	if (!redir)
		return (NULL);
	while (redir)
	{
		node = redir->next;
		free(redir->file);
		free(redir);
		redir = node;
	}
	return (NULL);
}