/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:30:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/12/05 17:35:12 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_redir_name(t_token **tokens, t_type redir_type)
{
	int		i;
	char	*file;

	file = NULL;
	i = 0;
	while (*tokens)
	{
		if ((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED
			|| (*tokens)->type == SINGLE_QUOTED)
		{
			file = ft_free_strjoin(file, (*tokens)->command);
		}
		else if ((*tokens)->type == SEPERATOR || (*tokens)->type == PIPE || \
				(*tokens)->type == REDIR_INPUT || (*tokens)->type == HEREDOC || \
				(*tokens)->type == REDIR_OUTPUT || \
				(*tokens)->type == REDIR_OUTPUT_APPEND)
		{
			if (!(redir_type == REDIR_OUTPUT && \
			(*tokens)->type == PIPE && i == 0))
				break ;
		}
		i++;
		*tokens = (*tokens)->next;
	}
	return (file);
}

void	init_redir(t_redir **redir)
{
	if (!*redir)
	{
		(*redir) = ptr_check(malloc(sizeof(t_redir)));
		(*redir)->lst = NULL;
		(*redir)->stdin_cpy = dup(STDIN_FILENO);
		(*redir)->stdout_cpy = dup(STDOUT_FILENO);
	}
}

int	if_redir_no_heredoc(t_type type)
{
	if (type == REDIR_INPUT || type == REDIR_OUTPUT
		|| type == REDIR_OUTPUT_APPEND || type == PIPE)
		return (0);
	return (1);
}

int	handle_redirections(t_redir **redir, t_token **tokens, t_env *env)
{
	t_type	redir_type;
	char	*file;

	file = NULL;
	init_redir(redir);
	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == SEPERATOR)
		*tokens = (*tokens)->next;
	file = get_redir_name(tokens, redir_type);
	if (!file)
	{
		destroy_redir((*redir));
		ft_putstr_fd("Redirection error\n", STDERR_FILENO);
		env->exit_status = 2;
		return (1);
	}
	push_redir(&(*redir)->lst, lst_redir_new(file, redir_type));
	free(file);
	return (0);
}
