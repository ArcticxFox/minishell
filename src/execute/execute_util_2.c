/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 15:58:49 by ejones            #+#    #+#             */
/*   Updated: 2026/07/13 12:30:16 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(char **env, char *line)
{
	char	*tmp;

	tmp = expand(env, line, TOKEN_WORD, 1);
	if (!tmp)
		return (NULL);
	free(line);
	return (tmp);
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
		shell->exit_value = 128 + WTERMSIG(last_status);
}
