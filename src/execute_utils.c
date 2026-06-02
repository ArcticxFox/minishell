/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:43:20 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/02 16:14:51 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_fork(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	pid_t	pid;

	if (is_builtin(cmd))
		builtin(cmd->args, shell);
	else
	{
		path = get_path(cmd->cmd, shell);
		if (path == NULL)
			return ;
		pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			return ;
		}
		if (pid == 0)
		{
			execve(path, cmd->args, shell->env);
			perror(path);
			exit (127);
		}
		else
			waitpid(pid, NULL, 0);
		free(path);
	}
}

int execute_single(t_cmd *list, t_shell *shell)
{
	int		saved_in;
	int		saved_out;
	t_cmd	*current;
	t_cmd	*cmd_node;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	current = list;
	cmd_node = NULL;
	while (current && current->tk_type != TOKEN_PIPE)
	{
		if (current->tk_type != TOKEN_WORD)
			apply_redir(current);
		else
			cmd_node = current;
		current = current->next;
	}
	if (cmd_node)
		execute_fork(cmd_node, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}

void	execute_redir(t_cmd *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->tk_type == TOKEN_REDIR_IN)
	{
		fd = open(cmd->cmd, O_RDONLY);
		if (fd >= 0)
			dup2(fd, STDIN_FILENO);
	}
	else if (cmd->tk_type == TOKEN_REDIR_OUT)
	{
		fd = open(cmd->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd >= 0)
			dup2(fd, STDOUT_FILENO);
	}
	else if (cmd->tk_type == TOKEN_APPEND)
	{
		fd = open(cmd->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd >= 0)
			dup2(fd, STDOUT_FILENO);
	}
	if (fd < 0)
		return ;
	close(fd);
}

execute_pipeline(t_cmd *list, t_shell *shell)
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

	prev_fd = -1;
	while (list != NULL)
	{
		if(list->next != NULL)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (list->next != NULL)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execute_single(list, shell);
			exit (127);
			if (pid > 0)
			{
				if (prev_fd != -1)
					close (prev_fd);
				if (list->next != NULL)
				{
					close(pipefd[1]);
					prev_fd = pipefd[0];
				}
			}
		}
	}
}

int	is_builtin(char *cmd)
{
	static t_builtin	builtin[8] = {
	{"pwd", NULL},
	{"echo", NULL},
	{"exit", NULL},
	{"env", NULL},
	{"cd", NULL},
	{"export", NULL},
	{"unset", NULL},
	{NULL, NULL}
	};
	int					i;

	i = 0;
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, ft_strlen(builtin[i].name) + 1))
			return (1);
		i++;
	}
	return (0);
}
