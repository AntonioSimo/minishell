/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:20:24 by pskrucha          #+#    #+#             */
/*   Updated: 2023/09/13 14:45:59 by pskrucha         ###   ########.fr       */
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
		return (NULL);
	temp_arr = ptr_check(ft_split(expanded, ' '));
	expanded = ft_free(expanded);
	while (temp_arr[i])
	{
		token = ptr_check(ft_strdup(temp_arr[i]));
		push_token(&new_nodes, lst_token_new(token, DEFAULT));
		free(token);
		i++;
	}
	temp_arr = double_free(temp_arr);
	print_expanded_nodes(new_nodes);
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

t_token	*create_nodes(char *expanded, char	*str, int start, int end)
{
	char	*before;
	char	*after;
	t_token	*temp_node;

	temp_node = NULL;
	before = ft_substr(str, 0, start - 1);
	after = ft_substr(str, end, ft_strlen(str) - end);
	if (ft_strlen(before))
		push_token(&temp_node, lst_token_new(before, DEFAULT));
	if (ft_strlen(expanded))
		push_token(&temp_node, lst_token_new(expanded, DEFAULT));
	if (ft_strlen(after))
		push_token(&temp_node, lst_token_new(after, DEFAULT));
	free(before);
	free(after);
	return (temp_node);
}

void	free_node(t_token *token)
{
	free(token->command);
	free(token);
}

void	connect_nodes(t_token *new_nodes, t_token **tokens, int pos, t_token **head)
{
	int i = 0;
	t_token	*or_head;
	t_token	*next_head;
	t_token	*prev_to_append;
	// t_token	*to_free;
	(void)tokens;
	or_head = *head;
	while (i<pos)
	{
		*head = (*(head))->next;
		if (i<pos - 1)
			prev_to_append = *head;
		i++;
	}
	printf("head:%s\n", (*head)->command);
	i = 0;
	// to_free = (*head);
	// free(to_free->command);
	// free(to_free);
	next_head = (*head)->next;
	// printf("to free: %s\n", next_head->command);
	// if ((*head)->next->next)
	// {
		// next_head = (*head)->next->next;
	// }
	prev_to_append->next = new_nodes;
	while (new_nodes->next)
		new_nodes = new_nodes->next;
	new_nodes->next = next_head;
	*head = or_head;
}

static void	dollar_expansion(t_token *tokens, t_envepval *my_env)
{
	// char	*new_command;
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
			break ;
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
			// expanded_nodes = create_new_nodes(expanded);
			if (brackets) //to get rid of the {}
			{
				j--;
				i++;
			}
			printf("%s\n", expanded);
			expanded_nodes = create_nodes(expanded, tokens->command, j, i);
			print_expanded_nodes(expanded_nodes);
			// printf("new command: %s\n", new_command);
			// ft_free(tokens->command);
			// tokens->command = ft_strdup(new_command);
			connect_nodes(expanded_nodes, &tokens, 0, &tokens);
			// ft_free(new_command);
			ft_free(to_expand);
			// ft_free(expanded);
			i = 0;
			brackets = false;
		}
		else
		{
			i++;
			while (tokens->command[i] && tokens->command[i] != '$')
				i++;
		}
	}
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

void	double_dollar(t_token *tokens)
{
	char	*new_command;
	char	*pid;
	size_t		i;

	i = 0;
	pid = ft_itoa((int)getpid());
	while (ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)))
	{
		i = ft_strlen(tokens->command) - ft_strlen(ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)));
		new_command = replace_string(pid, tokens->command, i + 1, i + 2);
		free(tokens->command);
		tokens->command = ptr_check(ft_strdup(new_command));
		free(new_command);
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

void	expander(t_token *tokens, t_envepval *my_env, char *or_home)
{
	
	while (tokens)
	{
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strnstr(tokens->command, "$?", ft_strlen(tokens->command)))
			error_code_expansion(tokens);
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strchr(tokens->command, '$'))
			dollar_expansion(tokens, my_env);
		if ((tokens->type == DEFAULT || tokens->type == DOUBLE_QUOTED)
			&& ft_strnstr(tokens->command, "$$", ft_strlen(tokens->command)))
			double_dollar(tokens);
		if (tokens->type == DEFAULT && tokens->command[0] == '~')
			tilde_expansion(tokens, my_env, or_home);
		tokens = tokens->next;
	}
}