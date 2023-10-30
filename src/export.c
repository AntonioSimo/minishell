#include "../include/minishell.h"

t_envepval	*create_env_emptynode(char *key)
{
	t_envepval	*node;

	node = ptr_check(malloc(sizeof(t_envepval)));
	node->key = ptr_check(ft_strdup(key));
	node->val = malloc(1);
	node->val[0] = 0;
	node->next = NULL;
	return (node);
}

void	print_my_export(t_envepval *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}

int	ft_isvariable(char *args)
{
	if (*args == '=')
		return (0);
	while (*args && *args != '=')
	{	
		if (!*args || ft_isdigit(*args) || *args == '=' || (*args == '$' && !*(args + 1)) || *args == ' ')
		{
			return (0);
		}
		if (*args == ' ' || *args == '+' || *args == '-')
		{
			return (0);
		}
		args++;
	}
	return (1);
}

void	add_env_variable(t_envepval **lst, t_envepval *new)
{
	t_envepval	*previous_variable;

	previous_variable = *lst;
	if (previous_variable == NULL)
	{
		*lst = new;
		return ;
	}
	while (previous_variable && ft_strcmp(previous_variable->key, new->key) != 0)
	{
		previous_variable = previous_variable->next;
	}
	if (!previous_variable)
	{
		previous_variable = lstenv(*lst);
		previous_variable->next = new;
		return ;
	}
	free(previous_variable->val);
	previous_variable->val = new->val;
	free(new->key);
	free(new);
}

t_envepval	*set_newvariable(char *args)
{
	char			*key;
	char			*val;
	t_envepval		*variable;

	if (!args)
		return (NULL);
	val = ft_strchr(args, '=');
	key = ft_substr(args, 0, (ft_strlen(args) - ft_strlen(val)));
	val++;
	variable = create_env_node(key, val);
	return (variable);
}

void	ft_export(t_env *env, char **args)
{
	t_envepval	*new_variable;
	t_envepval	*empty_variable;
	int			i;

	i = 1;
	if (!args[i])
	{
		print_my_export(env->env);
		env->exit_status = SUCCESS;
	}
	while (args[i] != NULL)
	{
		if (ft_isvariable(args[i]) == 1)
		{
			if (!ft_strchr(args[i], '='))
			{
				if (!ft_strcmp(find_expandable(env->env, args[i]), ""))
				{
					empty_variable = create_env_emptynode(args[i]);
					add_env_variable(&(env->env), empty_variable);
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
			ft_print_message("mustash: export: `", args[i], "': not a valid identifier\n", STDERR_FILENO);
			env->exit_status = ERROR;
		}
		i++;
	}
}
