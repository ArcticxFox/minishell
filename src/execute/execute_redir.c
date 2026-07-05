/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/05 19:29:12 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	wait_heredoc(int *pipefd, t_redir *redir, pid_t pid)
{
	int		status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(pipefd[0]);
		g_value_exit = 130;
		return (-1);
	}
	redir->heredoc_fd = pipefd[0];
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

int	handle_heredoc(t_redir *redir, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (-1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		init_signals();
		return (-1);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		read_heredoc_lines(pipefd[1], redir, env);
		close(pipefd[1]);
		exit(0);
	}
	return (wait_heredoc(pipefd, redir, pid));
}

int	setup_heredocs(t_cmd *head, char **env)
{
	t_redir	*redir;

	while (head)
	{
		redir = head->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				if (handle_heredoc(redir, env) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		head = head->next;
	}
	return (0);
}

void	execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	char	**real_args;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	real_args = get_args_for_execve(cmd->args);
	if (apply_redirs(cmd->redir) < 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		child_exit(shell, 1, real_args);
	}
	g_value_exit = builtin(real_args, shell);
	free_memory(real_args);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
