/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 14:59:55 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/14 13:38:27 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	free_pipes(int **pipes, int i)
{
	while (i > 0)
	{
		i--;
		free(pipes[i]);
	}
	free(pipes);
}

void	close_all_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**create_pipes(int n)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(sizeof(int *) * n);
	if (!pipes)
		return (NULL);
	while (i < n)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			free_pipes(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) < 0)
		{
			free_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	child_pipe_setup(t_cmd *cmd, t_pipe_state *state, t_shell *shell)
{
	int	fd_in;
	int	fd_out;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (state->index == 0)
		fd_in = STDIN_FILENO;
	else
		fd_in = state->pipes[state->index - 1][0];
	if (state->index == state->n_cmds - 1)
		fd_out = STDOUT_FILENO;
	else
		fd_out = state->pipes[state->index][1];
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	close_all_pipes(state->pipes, state->n_cmds - 1);
	free_pipes(state->pipes, state->n_cmds - 1);
	free(state->pids);
	execute_child(cmd, STDIN_FILENO, STDOUT_FILENO, shell);
}
