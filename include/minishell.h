/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimone <asimone@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:52 by asimone           #+#    #+#             */
/*   Updated: 2023/12/12 17:28:17 by asimone          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\x1b[32;01m"
# define BOLD "\033[1m"
# define RESET  "\x1b[0m"
# define PATH_MAXSIZE 1024

// Exit_STATUS
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127
# define TERMINATION_SIGINT 130
# define TERMINATION_SIGTERM 143

# include "../lib/Libft/include/libft.h"

# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum e_type
{
	DEFAULT,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	REDIR_INPUT,
	HEREDOC,
	REDIR_OUTPUT,
	REDIR_OUTPUT_APPEND,
	PIPE,
	SEPERATOR
}	t_type;

typedef struct s_redir
{
	int					stdin_cpy;
	int					stdout_cpy;
	struct s_redir_lst	*lst;
}	t_redir;

typedef struct s_redir_lst
{
	char				*file;
	bool				quotes;
	t_type				type;
	int					fd;
	struct s_redir_lst	*next;
}	t_redir_lst;

typedef struct s_command
{
	char				**arguments;
	char				*command;
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;

typedef struct s_dollar
{
	char	*to_expand;
	char	*expanded;
	int		i;
	int		j;
	bool	brackets;
	int		pos;
}	t_dollar;

typedef struct s_env
{
	struct s_envepval	*env;
	int					exit_status;
	char				**env_copy;
}	t_env;

typedef struct s_envepval
{
	char				*key;
	char				*val;
	struct s_envepval	*next;
}	t_envepval;

typedef struct s_execution
{
	t_command			*head;
	int					**fd;
	pid_t				*pid;
	int					i;
	int					cmds_size;
}	t_execution;

typedef struct s_token
{
	char				*command;
	t_type				type;
	struct s_token		*next;
}	t_token;

typedef struct s_expander
{
	int					i;
	t_token				*head;
	int					old_pos;
	t_type				prev_type;
	bool				move_ptr;
	bool				if_expand;
}	t_expander;

typedef struct s_parsing
{
	char	*word;
	char	**args_arr;
}	t_parsing;

extern int	g_signal;

//builtin
int			ft_isbuiltin(char *command);
void		exe_builtin(t_command *cmd, t_env *env, int exit_status);

//cd
char		*get_cwd(t_env *env);
char		*get_old_pwd(t_env *env);
char		*get_pwd(t_env *env);
void		update_wd(t_env *env, char *wd, char *new_wd_value);
void		ft_cd(t_env *env, t_command *cmd);

//commands_utils
t_command	*lst_cmd_new(char **args, t_redir *redir);
void		push_cmd(t_command **lst, t_command *new);
void		print_cmds(t_command *cmd_lst);
void		*destroy_cmds(t_command	*cmd_lst);

//dollar_expansion
t_dollar	*set_var_dollar(int pos);
void		expand_token(t_token *tokens, t_dollar *var, t_token **head, \
			t_envepval *my_env);
int			dollar_expansion(t_token *tokens, t_envepval *my_env, \
			t_token **head, int pos);
void		double_dollar(t_token *tokens, t_token **head, int pos);

//env
t_envepval	*create_env_node(char *key, char *value);
void		print_my_env(t_env *env);
void		set_env(t_envepval	**my_env, char **env);

//env2
t_env		*copy_env(char **env);
int			lstenv_c(t_envepval *lst);
char		*env_str(t_envepval *current);
char		**get_envp(t_env *env);

//env3
t_envepval	*lstenv(t_envepval *lst);
void		envlst_add(t_envepval **lst, t_envepval *new);
size_t		env_len(t_envepval *env);
void		replace_env_copy(t_env **env);

//echo
int			ft_arraysize(char **args);
void		check_nl(char **args, bool *is_nl, int j, bool *if_print);
void		echo_token(bool *valid, char **args, int j);
void		echo_command(char **args, t_env *env);

//error
void		perror_exit(char *str);
void		strerror_exit(void);
void		*ptr_check(void *ptr);
void		ft_print_message(char *command, char *str, \
			char *error_message, int fd);

//execution
t_execution	*initialize_temp(t_command *cmds);
void		find_cmd(t_command	*cmd, t_env *env);
void		is_executable(t_command *cmds, t_env *env);
void		handle_child_process(int **fd, t_command *cmds, t_env *env, \
			t_execution	*temp);
void		wait_last_child(t_command *cmds, int last_pid, t_env *env);

//execution2
void		close_pipes(int **fd, t_execution *temp);
void		free_temp(t_execution *temp);
int			run_commands(t_command *cmds, t_env *env);

//exit
int64_t		ft_atoint64_t(const char *str);
bool		ft_isnumber(char *str);
void		ft_exit(char **args, t_env *env);

//expander_checkers
int			is_double_dollar(t_token **tokens, bool check);
int			is_single_dollar(t_token **tokens, bool check);
int			is_error_code(t_token **tokens, bool if_expand);
void		handle_error_code(t_token **tokens, t_token **head, \
			t_expander *var, t_env *env);
void		check_prev_token(t_token **tokens, t_expander *var);

//expander_utils
t_token		*create_nodes(char *expanded, t_token *token, int start, int end);
int			char_to_expand(char c);
void		error_code_expansion(t_token *token, t_token **head, \
			int pos, t_env *env);
void		check_if_expand(t_expander *var, t_type type);

//expander
t_expander	*set_var(t_token **tokens);
void		single_dollar(t_token **tokens, t_envepval *my_env, \
			t_token **head, t_expander *var);
void		handle_double_dollar(t_token **tokens, t_token **head, \
			t_expander *var);
void		expander(t_token **tokens, t_env *my_env);

//export_utils
t_envepval	*create_env_emptynode(char *key);
void		print_my_export(t_envepval *env);
int			ft_isvariable(char *args);

//export
t_envepval	*set_newvariable(char *args);
void		add_env_variable(t_envepval *lst, t_envepval *new);
void		ft_export(t_env *env, char **args);

//heredoc
int			heredoc(t_redir_lst *redir, t_env *env);
void		child_process_here_doc(t_redir_lst *redir, int *pipe_fd, \
			t_env *env);
int			init_heredoc(t_execution *temp, t_env *env);
void		clear_redir_lst(t_execution *temp);

//lexer
int			is_divider(t_type type);
int			check_pipes(t_token **tokens, t_env *env, char **line);
int			lexer(char **line, t_env *my_env);
int			cat_line(t_token **tokens, t_env *env, char **line, int *ctrl_c);

//main
void		minishell(t_env *my_env);

//parsing
t_parsing	*set_parsing_var(void);
int			handle_redirections(t_redir **redir, t_token **tokens, t_env *env);
void		handle_cmds(t_token *tokens, t_command **commands, \
						t_redir **redir, t_parsing **var);

//parsing2
int			not_pipe(t_type type);
int			check_if_redir(t_type type);
int			free_parsing_temp(t_parsing *temp, int check);
t_command	*merge_tokens(t_token	*tokens, t_env *env);

//pwd
void		get_current_working_dir(t_env *env);

//quotes
t_type		quotes_type(char *line, int pos);
void		skip_quotes(char *line, int *i, t_type *quotes);
int			strlen_quoted(char *line, int position, t_type quotes_type);
bool		check_quotes(char *line);

//redirections_utils
void		print_redirections(t_redir_lst	*redir);
t_redir_lst	*lst_redir_new(char	*file, t_type type, bool quotes);
t_redir_lst	*redir_lst_last(t_redir_lst *redir);
void		push_redir(t_redir_lst **redir_lst, t_redir_lst *redir);

//redirections_utils2
void		*destroy_redir_lst(t_redir_lst *redir);
void		*destroy_redir(t_redir *redir);
void		execute_pipe(int **fd, t_execution *temp);
void		alloc_in_n_out(t_redir **redir);

//redirections
void		reset_stdout_stdin(t_redir *redir);
int			count_redir(t_redir_lst *redir, t_type type);
int			run_redirections(t_redir *redir, t_env *env);
int			handle_redir_in(t_redir_lst *temp);
int			handle_redir_out(t_redir_lst *temp);

//signals
void		ctrl_c_child(int sig);
void		manage_signals(int control);
void		ctrl_c_handler(int sig);

//tilde
int			if_tilde(t_token **tokens, t_expander	*var);
char		*replace_string(char *expanded, char	*str, int start, int end);
void		tilde_expansion(t_token *tokens, t_envepval *my_env);
char		*find_home(t_envepval *env);

//tokanization
void		tokenize_space(t_token **token_lst, char *line, int *i);
void		tokenize_symbols(t_token **token_lst, char *line, int *i);
void		tokenize_word(t_token **token_lst, char *line, int *position);
void		tokenize_quotted(t_token **token_lst, char *line, int *pos, \
							t_type quotes);
t_token		*tokenize(char *line);

//token_symbols
void		tokenize_pipe(t_token **token_lst, int *i);
void		tokenize_redir_in(t_token **token_lst, int *i);
void		tokenize_redir_out(t_token **token_lst, int *i);
void		tokenize_redir_outapp(t_token **token_lst, int *i);
void		tokenize_heredoc(t_token **token_lst, int *i);

//token_utils
t_token		*lst_token_new(char *str, t_type type);
void		push_token(t_token **lst, t_token *new);
void		print_tokens(t_token *token_lst);
void		*destroy_tokens(t_token	*tokens);

//token_utils2
int			token_lst_size(t_token	*tokens);
t_token		*create_token(char *string, t_type type);
void		attach_empty_head(int pos, t_token **head, t_token *or_head);
void		attach_head(int pos, t_token **head, t_token *or_head);
int			not_pipe(t_type type);

//token_utils3
void		connect_nodes(t_token *new_nodes, int pos, t_token **head);
t_token		*create_new_nodes(char *expanded, t_type type);
int			check_and_append(char *extra_line, t_token **tokens, t_env *env, \
							char **line);

//unset
void		ft_nodedel(t_envepval *env);
void		ft_unset(t_env *env, char **args);

//utils
int			ft_isspace(int c);
int			find_equal(char *line);
char		*find_path(char *cmd, char *envp);
void		*ft_ptrdel(void *ptr);
void		*double_free(char **ptr);

//utils2
char		**push_str_2d(char **args, char *str);
int			free_env(t_env *env);

//utils3
char		*find_expandable(t_envepval	*env, char	*key);
int			ft_strcmp(char *s1, char *s2);
int			is_word(t_type type);
int			count_cmds(t_command *cmds);
int			strlen_2d(char **str);

//lexer3
int			is_divider(t_type type);
int			if_not_space(t_token *tokens);

//heredoc_expander
char		*expand_heredoc(char *line, t_env *env);
char		**handle_error_code_heredoc(char **line, t_env *env);
char		**get_new_line(char **line, int j, char *pid, int check);

//heredoc_expander_utils
int			if_expand(char **line);
char		*find_dollar(char **str);
int			if_error_expansion_here(char **str);
int			if_double_dollar_here(char **str);
int			if_here_dollar(char **str);
char		**append_str(char **array, char *str);
char		**make_2d_expanded(char *expanded, char	*str, int start, int end);
char		**append_strings(char **line, char **extra_strings, int pos);

#endif