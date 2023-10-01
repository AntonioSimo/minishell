/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/01 17:54:59 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int g_error_code;

int	char_to_expand(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*find_expandable(t_envepval	*env, char	*key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(env->key))
			&& !ft_strncmp(key, env->key, ft_strlen(key)))
			return (ft_strdup(env->val));
		env = env->next;
	}
	return (ft_strdup(""));
}

void	print_expanded_nodes(t_token *nodes)
{
	while (nodes)
	{
		printf("%s\n", nodes->command);
		nodes = nodes->next;
	}
}

t_token	*create_new_nodes(char *expanded)
{
	char	**temp_arr;
	t_token	*new_nodes;
	int		i;
	char	*token;

	i = 0;
	new_nodes = NULL;
	if (ft_strlen(expanded) == 0)
	{
		push_token(&new_nodes, lst_token_new("", DEFAULT));
		return (new_nodes);
	}
	temp_arr = ptr_check(ft_split(expanded, ' '));
	while (temp_arr[i])
	{
		token = ptr_check(ft_strdup(temp_arr[i]));
		push_token(&new_nodes, lst_token_new(token, DEFAULT));
		if (temp_arr[i + 1])
			push_token(&new_nodes, lst_token_new(" ", SEPERATOR));
		free(token);
		i++;
	}
	temp_arr = double_free(temp_arr);
	return (new_nodes);
}

char	*replace_string(char *expanded, char	*str, int start, int end)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*new_line;
	
	before = ft_substr(str, 0, start - 1);
	after = ft_substr(str, end, ft_strlen(str) - end);
	temp = ft_strjoin(before, expanded);
	new_line = ft_strjoin(temp, after);
	free(temp);
	free(before);
	free(after);
	return (new_line);
}

int	token_lst_size(t_token	*tokens)
{
	int		i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);

}

t_token	*create_nodes(char *expanded, char	*str, int start, int end)
{
	char	*before;
	char	*after;
	t_token	*temp_node;
	t_token	*expanded_nodes;
	int		i = 0;
	t_token	*temp_expanded;

	temp_node = NULL;
	before = ft_substr(str, 0, start - 1);
	after = ft_substr(str, end, ft_strlen(str) - end);
	if (ft_strlen(before) > 0)
		push_token(&temp_node, lst_token_new(before, DEFAULT));
	if (ft_strlen(expanded) > 0)
	{
		expanded_nodes = create_new_nodes(expanded);
		i = token_lst_size(expanded_nodes);
		while (i)
		{
			temp_expanded = expanded_nodes->next;
			expanded_nodes->next = NULL;
			push_token(&temp_node, expanded_nodes);
			expanded_nodes = temp_expanded;
			i--;
		}
	}
	if (ft_strlen(after) > 0)
		push_token(&temp_node, lst_token_new(after, DEFAULT));
	free(before);
	free(after);
	if (!temp_node)
		return (lst_token_new("", DEFAULT));
	return (temp_node);
}

void	free_node(t_token *token)
{
	free(token->command);
	free(token);
}

void	connect_nodes(t_token *new_nodes, int pos, t_token **head)
{
	int i = 0;
	t_token	*or_head;
	t_token	*next_head;
	t_token	*prev_to_append;

	or_head = *head;
	prev_to_append = *head;
	while (i<pos)
	{
		*head = (*(head))->next;
		if (i == pos - 2)
			prev_to_append = *head;
		i++;
	}
	i = 0;
	next_head = (*head)->next;
	prev_to_append->next = new_nodes;
	while (new_nodes->next)
		new_nodes = new_nodes->next;
	new_nodes->next = next_head;
	if (pos == 0)
		*head = or_head->next;
	else
		*head = or_head;
}

static int	dollar_expansion(t_token *tokens, t_envepval *my_env, t_token **head, int pos)
{
	char	*to_expand;
	char	*expanded;
	int 	i;
	int		j;
	bool	brackets;
	t_token	*expanded_nodes;

	j = 0;
	i = 0;
	while(i < (int)ft_strlen(tokens->command))
	{
		if (tokens->command[i] == '$' && !tokens->command[i + 1]) //to leave $ at the last position $USER$
			return (1);
		if (tokens->command[i] == '$' && tokens->command[i + 1] //to skip $$ 
			&& tokens->command[i + 1] == '$')
				i += 2;
		if (tokens->command[i] && tokens->command[i] == '$')
		{
			i++;
			if (tokens->command[i] == '{')
			{
				brackets = true;
				i++;
			}
			j = i;
			while (tokens->command[i] && char_to_expand(tokens->command[i]))
				i++;
			to_expand = ft_substr(tokens->command, j, i - j);	
			expanded = find_expandable(my_env, to_expand);
			if (brackets) //to get rid of the {}
			{
				j--;
				i++;
			}
			printf("start:%i, end:%i", j, i);
			expanded_nodes = create_nodes(expanded, tokens->command, j, i);
			printf("new nodes:\n");
			connect_nodes(expanded_nodes, pos, head);
			print_tokens(*head);
			printf("after\n\n");
			ft_free(to_expand);
			break ;
		}
		else
		{
			i++;
			while (tokens->command[i] && tokens->command[i] != '$')
				i++;
		}
	}
	return (0);
}

static void tilde_expansion(t_token *tokens, t_envepval *my_env, char *or_home)
{
	char	*home;
	char	*new_command;

	home = find_expandable(my_env, "HOME");
	if (ft_strlen(home) == 0)
	{
		free(home);
		home = ft_strdup(or_home);
	}
	new_command = replace_string(home, tokens->command, 1 , 1);
	free(tokens->command);
	tokens->command = ft_strdup(new_command);
	free(new_command);
	free(home);
}

void	double_dollar(t_token *tokens, t_token **head, int pos)
{
	// char	*new_command;
	char	*pid;
	size_t		i;
	t_token	*new_nodes;

	i = 0;
	pid = ft_itoa((int)getpid());
	while (i < ft_strlen(tokens->command))
	{
		if (ft_strlen(tokens->command + i) > 1 && tokens->command[i] == '$'
			&& tokens->command[i + 1] == '$')
		{
			
			i = ft_strlen(tokens->command) - ft_strlen(ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)));
			new_nodes = create_nodes(pid, tokens->command, i + 1, i + 2);
			connect_nodes(new_nodes, pos, head);
			break ;
		}
		i++;
		// free(tokens->command);
		// tokens->command = ptr_check(ft_strdup(new_command));
		// free(new_command);
	}
	free(pid);
}

void	error_code_expansion(t_token *token)
{
	char	*new_command;
	char	*error_code;
	int		i;

	i = 0;
	error_code = ptr_check(ft_itoa(g_error_code));
	while (ft_strnstr(token->command, "$?", ft_strlen(token->command)))
	{
		i = ft_strlen(token->command) - ft_strlen(ft_strnstr(token->command, "$?", ft_strlen(token->command)));
		new_command = replace_string(error_code, token->command, i + 1, i + 2);
		free(token->command);
		token->command = ptr_check(ft_strdup(new_command));
		free(new_command);
	}
	free(error_code);
}

void	expander(t_token **tokens, t_envepval *my_env, char *or_home)
{
	t_token	*head;
	int		i;
	bool	move_ptr;
	bool	check;

	i = 0;
	head = *tokens;
	while (*tokens)
	{
		check = true;
		move_ptr = true;
		if (check && ((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strnstr((*tokens)->command, "$?", ft_strlen((*tokens)->command)))
			error_code_expansion(*tokens);
		if (check && ((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strnstr((*tokens)->command, "$$", ft_strlen((*tokens)->command)))
			{
				printf("here\n");
				double_dollar(*tokens, &head, i);
				i = 0;
				*tokens = head;
				move_ptr = false;
				check = false;
				printf("here out\n");
			}
		if (check && ((*tokens)->type == DEFAULT || (*tokens)->type == DOUBLE_QUOTED)
			&& ft_strchr((*tokens)->command, '$') && ft_strlen((*tokens)->command) != 1)
			{
				printf("enter with string: %s\n", (*tokens)->command);
				if (!dollar_expansion(*tokens, my_env, &head, i))
				{
					i = 0;
					*tokens = head;
					move_ptr = false;
				}
			}
		if ((*tokens)->type == DEFAULT && (*tokens)->command[0] == '~')
			tilde_expansion((*tokens), my_env, or_home);
		if (move_ptr)
		{
			*tokens = (*tokens)->next;
			i++;
		}
	}
	*tokens = head;
}