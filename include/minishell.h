/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:31:52 by asimone           #+#    #+#             */
/*   Updated: 2023/10/05 17:40:45 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define  MINISHELL_H

# define GREEN "\x1b[32;01m"
# define RED "\x1b[31;01m"
# define YELLOW "\033[33;1m"
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
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdio.h>

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

typedef enum e_fileflags
{
	INVALID = -1,
	INPUT,
	INPUT_HEREDOC,
	INPUT_HEREDOC_LIT,
	OUTPUT,
	OUTPUT_APP
}	t_fileflags;

typedef enum e_character_category
{
	CHAR_WHITESPACE = ' ',
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_SINGLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_PARENTHESIS = ')',
	CHAR_NEW_LINE = '\n',
}	t_character_category;

/**
* @brief	This struct will return the user defined 
* @param arguments this is a pointer to the stirng ....
* @param command this is a pointer to the mlx image
* @param fd these are the fd for the Pipe.
* 					- fd_std[0]: Standard input.
*					- fd_std[1]: Standard output.
*					- fd_std[2]: Standard error output.
* @param rederection 
*/

typedef struct s_expander
{
	int		i;
	int		old_pos;
	t_type	prev_type;
	bool	move_ptr;
}	t_expander;

typedef struct s_redir_lst
{
	char				*file;
	t_type				type;
	struct	s_redir_lst	*next;
}	t_redir_lst;

typedef struct s_redir
{
	int					*fileout;
	int					*filein;
	int					stdin_cpy;
	int					stdout_cpy;
	struct s_redir_lst	*lst;
}	t_redir;

typedef struct s_command
{
	char				**arguments;
	char				*command;
	// int					fd[2];
	t_redir				*redirections;
	struct s_command	*next;
}	t_command;


typedef struct s_file
{
	char		*name;
	t_fileflags	flag;
}	t_file;

typedef struct s_envepval
{
	char				*key;
	char				*val;
	struct s_envepval	*next;
}				t_envepval;

typedef struct s_token
{
	char			*command;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
    struct s_envepval	*env;
	int					exit_status;
    char				**env_copy;
}	t_env;

extern int g_signal;

//expander_checkers
int	is_double_dollar(t_token **tokens);
int	is_single_dollar(t_token **tokens);
int	is_error_code(t_token **tokens);
void	handle_error_code(t_token **tokens, t_token **head, t_expander *var, t_env *env);
void	check_prev_token(t_token **tokens, t_expander *var);


//quotes
t_type	quotes_type(char *line, int pos);
void	skip_quotes(char *line, int *i, t_type *quotes);
int		strlen_quoted(char *line, int position, t_type quotes_type);
bool	check_quotes(char *line);

//error
void	perror_exit(char *str);
void	strerror_exit();
void	*ptr_check(void *ptr);

void	parse(char *line);
void	lexer(char *line, t_env *my_env);

//executions
void	run_commands(t_command *cmds, t_env *env);
void    redir_out(t_command *cmd, t_env *env);

//tokenization
t_token	*create_token(char *string, t_type type);
void	tokenize_space(t_token **token_lst, char *line, int *i);
void	tokenize_symbols(t_token **token_lst, char *line, int *i);
void	tokenize(char *line, t_token **token_lst);

//utils
t_envepval	*create_env_node(char *key, char *value);
void		print_tokens(t_token *token_lst);
void		tokenize_pipe(t_token **token_lst, int *i);
void		tokenize_redir_in(t_token **token_lst, int *i);
void		tokenize_redir_out(t_token **token_lst, int *i);
void		tokenize_redir_outapp(t_token **token_lst, int *i);
void		tokenize_heredoc(t_token **token_lst, int *i);
int			ft_isspace(int c);
char		*find_path(char *cmd, char *envp);
int			find_equal(char *line);
void		*double_free(char **ptr);
char		*make_str_from_2d(char **args);
int			is_word(t_type type);

//utils2
char		**push_str_2d(char **args, char *str);
//parser
t_command	*merge_tokens(t_token	*tokens);
// void	parse_redirections(t_command *commands);

//expander
int			char_to_expand(char c);
int	dollar_expansion(t_token *tokens, t_envepval *my_env, t_token **head, int pos);
void	double_dollar(t_token *tokens, t_token **head, int pos);
void	expander(t_token **tokens, t_env *my_env);
char		*find_expandable(t_envepval	*env, char	*key);
void		connect_nodes(t_token *new_nodes, int pos, t_token **head);
t_token		*create_new_nodes(char *expanded);
char	*replace_string(char *expanded, char	*str, int start, int end);
void	connect_nodes(t_token *new_nodes, int pos, t_token **head);

//redirections
int	run_redirections(t_redir *redir, t_env *env);
void	close_redir(t_redir *redir);
int		count_redir(t_redir_lst *redir, t_type type);
//list utils
t_token		*lst_token_new(char *str, t_type type);
// void		lst_token_back(t_token **lst, t_token *new);
void		destroy_tokens(t_token	*tokens);
void		push_token(t_token **lst, t_token *new);

//env
void	set_env(t_envepval	**my_env, char **env);
void	print_my_env(t_envepval *my_env);
void  copy_env(char **env, t_env **main_env);
// t_env  *copy_env(char **env);
void   print_copy_env(t_env *env);

//tokens_utils2
int		token_lst_size(t_token	*tokens);

//expander_utils
t_token	*create_nodes(char *expanded, char	*str, int start, int end);
void	error_code_expansion(t_token *token, t_token **head, int pos, t_env *env);

//tilde
int		if_tilde(t_token **tokens, t_type prev_type);
void	tilde_expansion(t_token *tokens, t_envepval *my_env);
char	*find_home(t_envepval *env);

//command_utils
t_command	*lst_cmd_new(char **args, t_redir *redir);
void	push_cmd(t_command **lst, t_command *new);
void	print_cmds(t_command *cmd_lst);
void	*destroy_cmds(t_command	*cmd_lst);
void	push_redir(t_redir_lst **redir_lst, t_redir_lst *redir);
t_redir_lst	*redir_lst_last(t_redir_lst *redir);
t_redir_lst	*lst_redir_new(char	*file, t_type type);
void	*destroy_redir(t_redir_lst *redir);
void	print_redirections(t_redir_lst	*redir);

//executions
void	find_cmd(t_command	*cmd, t_env *env);
int		count_cmds(t_command *cmds);

//signals
void    signal_int_handler(int sig, siginfo_t *info, void *context);


//redirections
void	execute_pipe(int **fd, int i, t_command *head);


void 	echo_command(char **args);
void	exe_builtin(t_command *cmd, t_env *env, int exit_status);
int 	ft_isbuiltin(char *command);
int 	ft_arraysize(char **args);
void	get_current_working_dir(void);
bool	ft_isnumber(char *str, t_env *env);
void 	ft_exit(char **args, t_env *env);
int		ft_strcmp(char *s1, char *s2);
void 	ft_export(t_env *env, char **args);
void	ft_unset(t_env *env, char **args);
void	*ft_ptrdel(void *ptr);
void	ft_nodedel(t_envepval *env);

t_envepval *set_newvariable(char *args);

void	envlst_add(t_envepval **lst, t_envepval *new);
char    *get_cwd();
char    *get_pwd(t_env  *env);
void    update_pwd(t_env *env, char *pwd);
void	ft_cd(t_env *env, t_command *cmd);
t_envepval	*lstenv(t_envepval *lst);
int	ft_exit_status(char *msg, char *cmd, int exit_code, int return_val);
void	ft_print_message(char *command, char *str, char *error_message, int fd);

#endif