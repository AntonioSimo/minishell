/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:57:30 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/31 17:49:56 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parsing	*set_parsing_var(void)
{
	t_parsing	*var;

	var = ptr_check(malloc(sizeof(t_parsing)));
	var->args_arr = NULL;
	var->word = NULL;
	return (var);
}

int	handle_redirections(t_redir **redir, t_token **tokens, t_env *env)
{
	t_type	redir_type;
	char	*file;
	int		i;

	i = 0;
	file = NULL;
	if (!*redir)
	{
		(*redir) = ptr_check(malloc(sizeof(t_redir)));
		(*redir)->lst = NULL;
		(*redir)->stdin_cpy = dup(STDIN_FILENO);
		(*redir)->stdout_cpy = dup(STDOUT_FILENO);
		(*redir)->filein = NULL;
		(*redir)->fileout = NULL;
		(*redir)->in_count = 0;
		(*redir)->out_count = 0;
	}
	redir_type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && (*tokens)->type == SEPERATOR)
		*tokens = (*tokens)->next;
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
	if (!file)
	{
		ft_putstr_fd("Redirection error\n", STDERR_FILENO);
		env->exit_status = 2;
		return (1);
	}
	push_redir(&(*redir)->lst, lst_redir_new(file, redir_type));
	free(file);
	return (0);
}
