#include "../include/minishell.h"

void	set_env(t_list	**my_env, char **env)
{
	int i;
	char *key;
	char *value;
	int equal_pos;

	i = 0;
	while (env[i])
	{
		equal_pos = find_equal(env[i]);
		key = ft_substr(env[i], 0, equal_pos);
		value = ft_substr(env[i], equal_pos + 1, ft_strlen(env[i]) - equal_pos);
		ft_lstadd_back(my_env, ptr_check(ft_lstnew(create_env_node(key, value))));
		ft_free(key);
		ft_free(value);
		i++;
	}
}

void	print_val(t_envepval *node)
{
	ft_printf("key: %s | value: %s\n", node->key, node->val);
}

void	print_env(t_list *my_env)
{
	while (my_env)
	{
		print_val(my_env->content);
		my_env = my_env->next;
	}
}

void	loop(char **env)
{
	char *line;

	(void)env;
	while (1)
	{
		line = readline(GREEN BOLD "mustash> "RESET);
		if (!line)
			break ;
		add_history(line);
		lexer(line);
		free(line);
	}
}	

void	print_or_env(char **env)
{=
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

int	main(int argc, char** argv, char** env)
{
	(void) argv;
	(void) argc;
	t_list	*my_env = NULL;

	print_or_env(env);
	set_env(&my_env, env);
	print_env(my_env);

	

		loop(env);	
	exit (EXIT_SUCCESS);
}
