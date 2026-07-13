/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 00:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/13 11:29:33 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	wait_heredoc(int *pipefd, t_redir *redir, pid_t pid, t_shell *shell)
{
	int		status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		write(1, "\n", 1);
		close(pipefd[0]);
		shell->exit_value = 130;
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

int	handle_heredoc(t_cmd *head, t_redir *redir, char **env, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;

	g_heredoc_interrupt = 0;
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
		g_heredoc_interrupt = 0;
		signal(SIGINT, heredoc_sigint);
		close(pipefd[0]);
		read_heredoc_lines(pipefd[1], head, redir, env);
		free_heredoc(head, env, pipefd[1]);
		exit(0);
	}
	return (wait_heredoc(pipefd, redir, pid, shell));
}

int	setup_heredocs(t_cmd *head, t_redir *redir, char **env, t_shell *shell)
{
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (handle_heredoc(head, redir, env, shell) < 0)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

void	execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int		saved_in;
	int		saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	shell->current_cmd = cmd;
	if (apply_redirs(cmd->redir) < 0)
	{
		dup2(saved_in, STDIN_FILENO);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_in);
		close(saved_out);
		child_exit(shell, 1, cmd->args);
	}
	shell->exit_value = builtin(cmd->args, shell);
	free_memory(cmd->args);
	dup2(saved_in, STDIN_FILENO);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_in);
	close(saved_out);
}
