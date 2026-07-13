/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 15:58:49 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 19:41:33 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_shell *shell, char *line)
{
	char	*tmp;

	tmp = expand(shell, line, TOKEN_WORD, 1);
	if (!tmp)
		return (NULL);
	free(line);
	return (tmp);
}

void	wait_single_child(pid_t pid, t_shell *shell)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	init_signals();
	if (WIFEXITED(status))
		shell->exit_value = WEXITSTATUS(status);
	else
	{
		shell->exit_value = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
}

void	exit_status(t_pipe_state *state, t_shell *shell)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	status = 0;
	last_status = 0;
	while (i < state->n_cmds)
	{
		waitpid(state->pids[i], &status, 0);
		if (i == state->n_cmds - 1)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		shell->exit_value = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
	{
		shell->exit_value = 128 + WTERMSIG(last_status);
		if (WTERMSIG(last_status) == SIGINT)
			write(1, "\n", 1);
	}
}
