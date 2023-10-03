#include "../include/minishell.h"

t_export	*lstenv(t_export *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_export	*create_env_emptynode(char *key)
{
	t_export	*node;

	node = ptr_check(malloc(sizeof(t_export)));
	node->empty_key = ptr_check(ft_strdup(key));
	node->next = NULL;
	return (node);
}

void	print_my_export(t_env *env)
{
	t_export	*temp;

	temp = env->empty_key;
	print_my_env(env->env);
	while (temp)
	{
		ft_printf("%s\n", temp->empty_key);
		temp = temp->next;
	}
}

int    ft_isvariable(char *args)
{
	if (!*args || ft_isdigit(*args) || *args == '=' ||
		(*args == '$' && !*(args + 1)) || *args == ' ')
			return (0);
	while (*args && *args != '=')
	{
		if (*args == ' ' || *args == '+')
			return (0);
		args++;
	}
	return (1);
}

void    add_env_variable(t_envepval **lst, t_envepval *new)
{
	t_envepval	*lst_node;

	lst_node = *lst;
	if (lst_node == NULL)
	{
		*lst = new;
		return ;
	}
	while (lst_node->next != NULL)
	{       
		if (ft_strcmp(lst_node->key, new->key) == 0)
		{
			free(lst_node->val);
			lst_node->val = new->val;
			free(new->key);
			free(new);
			return ;
		}
		lst_node = lst_node->next;
	}
	if (ft_strcmp(lst_node->key, new->key) == 0)
	{
		free(lst_node->val);
		lst_node->val = new->val;
		free(new->key);
		free(new);
		return ;
	}
	lst_node->next = new;
}

void	exportlst_add(t_export **lst, t_export *new)
{
	t_export	*lst_node;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lst_node = lstenv(*lst);
	lst_node->next = new;
}

t_envepval *set_newvariable(char *args)
{
	char          *key;
	char          *val;
	t_envepval    *variable;

	if (!args)
		return (NULL);
	// if (!ft_strchr(args, '='))
	// {
	//     key = ft_substr(args, 0, (ft_strlen(args)));
	//     // val = "\0";
	//     variable = (t_envepval *)create_env_emptynode(key);
	// }
	//else
	val = ft_strchr(args, '=');
	key = ft_substr(args, 0, (ft_strlen(args) - ft_strlen(val)));
	val++;
	variable = create_env_node(key, val);
	// if (!variable->export_env->empty_val)
	//     variable->export_env = create_env_emptynode(key, val);
	// else
	return (variable);
}

void ft_export(t_env *env, char **args)
{
	t_envepval	*new_variable;
	t_export    *empty_value;
	int i;

	i = 1;
	// if (!args[i])
	// {
	// 	print_my_export(env);
	// 	return ;
	// }
	while (args[i] != NULL)
	{
		if (ft_isvariable(args[i]) == 1)
		{
			if (!ft_strchr(args[i], '='))
			{
					// print_my_env(env->env);
					// printf("my key: %s\n", find_expandable(env->env, args[i]));
				if (!ft_strcmp(find_expandable(env->env, args[i]), ""))
				{
					empty_value = create_env_emptynode(args[i]);
					exportlst_add(&(env->empty_key), empty_value);
				}
			}
			else
			{
				new_variable = set_newvariable(args[i]);
				if (new_variable != NULL)
					add_env_variable(&(env->env), new_variable);
			}
		}
		else
		{
			perror("mustash: variable not found");
			return ;
		}
	i++;
	}
}    
