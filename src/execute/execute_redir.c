/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/26 00:00:00 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	handle_file_redir(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == TOKEN_REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->file);
		return (-1);
	}
	if (redir->type == TOKEN_REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			dup2(redir->heredoc_fd, STDIN_FILENO);
			close(redir->heredoc_fd);
			redir->heredoc_fd = -1;
		}
		else if (handle_file_redir(redir) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	handle_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, redir->delimiter,
				ft_strlen(redir->delimiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipefd[1]);
		ft_putchar_fd('\n', pipefd[1]);
		free(line);
	}
	close(pipefd[1]);
	redir->heredoc_fd = pipefd[0];
	return (0);
}

void	setup_heredocs(t_cmd *head)
{
	t_redir	*redir;

	while (head)
	{
		redir = head->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				handle_heredoc(redir);
			redir = redir->next;
		}
		head = head->next;
	}
}

void	execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirs(cmd->redir) < 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		return ;
	}
	builtin(cmd->args, shell);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
