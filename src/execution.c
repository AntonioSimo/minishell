/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskrucha <pskrucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:07 by pskrucha          #+#    #+#             */
/*   Updated: 2023/10/05 17:01:32 by pskrucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmds(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		cmds = cmds->next;
		i++;
	}
	return (i);
}

void	find_cmd(t_command	*cmd, t_env *env)
{
	char	*path;

	path = find_path(cmd->command, find_expandable(env->env, "PATH"));
	printf("path: %s\n", path);
	if (path)
		execve(path, cmd->arguments, env->env_copy);
	else
		printf("%s: command not found\n", cmd->command);
	exit(EXIT_FAILURE);
}

int	count_redir(t_redir_lst *redir, t_type type)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	while (redir)
	{
		if ((type == REDIR_INPUT && redir->type == REDIR_INPUT)
			|| (type == REDIR_INPUT && redir->type == HEREDOC))
			in++;
		if ((type == REDIR_OUTPUT && redir->type == REDIR_OUTPUT)
			|| (type == REDIR_OUTPUT
				&& redir->type == REDIR_OUTPUT_APPEND))
			out++;
		redir = redir->next;
	}
	if (type == REDIR_INPUT)
		return (in);
	if (type == REDIR_OUTPUT)
		return (out);
	return (0);
}

void	run_redirections(t_redir *redir)
{
	int			i;
	int			j;
	t_redir_lst	*temp;

	i = 0;
	j = 0;
	temp = redir->lst;
	redir->fileout = ptr_check(malloc(sizeof(int) \
					* count_redir(temp, REDIR_OUTPUT)));
	redir->filein = ptr_check((malloc(sizeof(int) \
					* count_redir(temp, REDIR_INPUT))));
	redir->stdin_cpy = dup(STDIN_FILENO);
	redir->stdout_cpy = dup(STDOUT_FILENO);
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT || temp->type == REDIR_OUTPUT_APPEND)
		{
			if (temp->type == REDIR_OUTPUT)
				redir->fileout[i] = open(temp->file, O_WRONLY \
				| O_CREAT | O_TRUNC, 0644);
			if (temp->type == REDIR_OUTPUT_APPEND)
				redir->fileout[i] = open(temp->file, O_WRONLY \
				| O_CREAT | O_APPEND, 0644);
			if (redir->fileout[i] == -1)
				perror_exit("FD error\n");
			dup2(redir->fileout[i], STDOUT_FILENO);
			i++;
		}
		else if (temp->type == REDIR_INPUT)
		{
			redir->filein[j] = open(temp->file, O_RDONLY);
			if (redir->filein[j] == -1)
				perror_exit("FD error\n");
			dup2(redir->filein[j], STDIN_FILENO);
			j++;
		}
		temp = temp->next;
	}
}

void	close_redir(t_redir *redir)
{
	int			j;
	int			k;
	t_redir_lst	*temp;

	temp = redir->lst;
	j = 0;
	k = 0;

	dup2(redir->stdout_cpy, STDOUT_FILENO);
	dup2(redir->stdin_cpy, STDIN_FILENO);
	while (temp)
	{
		if (temp->type == REDIR_OUTPUT)
		{
			close(redir->fileout[j]);
			j++;
		}
		else if (temp->type == REDIR_INPUT)
		{
			close(redir->filein[j]);
			k++;
		}
		temp = temp->next;
	}
}

void	run_commands(t_command *cmds, t_env *env)
{
	int			**fd;
	int			i;
	pid_t		*pid;
	t_command	*head;

	i = 0;
	head = cmds;
	fd = NULL;
	if (count_cmds(cmds) == 1 && ft_isbuiltin(cmds->command))
	{
		if (cmds->redirections)
			run_redirections(cmds->redirections);
		exe_builtin(cmds->arguments, cmds->command, env, 0);
		if (cmds->redirections)
			close_redir(cmds->redirections);
		return ;
	}
	pid = ptr_check(malloc(sizeof(pid_t) * count_cmds(cmds)));
	if (count_cmds(cmds) > 1)
		fd = ptr_check(malloc(sizeof(int *) * count_cmds(cmds) - 1));
	while (i < count_cmds(cmds) - 1)
	{
		fd[i] = ptr_check(ft_calloc(2, sizeof(int)));
		if (pipe(fd[i]) == -1)
			return (perror_exit("Pipe error\n"));
		i++;
	}
	i = 0;
	while (cmds)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror_exit("Fork error\n"));
		if (pid[i] == 0)
		{
			execute_pipe(fd, i, head);
			if (cmds->redirections)
				run_redirections(cmds->redirections);
			if (ft_isbuiltin(cmds->command))
				exe_builtin(cmds->arguments, cmds->command, env, 1);
			find_cmd(cmds, env);
		}
		i++;
		cmds = cmds->next;
	}
	cmds = head;
	i = 0;
	while (i < count_cmds(cmds))
	{
		if (i < count_cmds(cmds) - 1)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		waitpid(pid[i], NULL, 0);
		i++;
	}
}
