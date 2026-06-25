/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:16:57 by ejones            #+#    #+#             */
/*   Updated: 2026/06/25 18:24:35 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell)
{
	char	*path;

	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	if (apply_redirs(cmd->redir) < 0)
		exit(1);
	if (is_builtin(cmd->cmd))
	{
		builtin(cmd->args, shell);
		exit(0);
	}
	path = get_path(cmd->cmd, shell);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror(path);
	free(path);
	exit(127);
}

void	execute_pipeline(t_cmd *list, t_shell *shell)
{
	t_pipe_state	state;
	pid_t			*pids;
	t_cmd			*current;
	int				i;

	state.n_cmds = count_cmds(list);
	state.pipes = create_pipes(state.n_cmds - 1);
	pids = malloc(sizeof(pid_t) * state.n_cmds);
	if (!state.pipes || !pids)
		return ;
	current = list;
	i = 0;
	while (current)
	{
		state.index = i;
		pids[i] = fork();
		if (pids[i] == 0)
			child_pipe_setup(current, &state, shell);
		current = current->next;
		i++;
	}
	close_all_pipes(state.pipes, state.n_cmds - 1);
	i = 0;
	while (i < state.n_cmds)
		waitpid(pids[i++], NULL, 0);
	free_pipes(state.pipes, state.n_cmds - 1);
	free(pids);
}

static void	execute_single_builtin(t_cmd *cmd, t_shell *shell)
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

void	execute_single(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd->cmd)
		return ;
	if (is_builtin(cmd->cmd))
	{
		execute_single_builtin(cmd, shell);
		return ;
	}
	pid = fork();
	if (pid == 0)
		execute_child(cmd, STDIN_FILENO, STDOUT_FILENO, shell);
	waitpid(pid, NULL, 0);
}

void	execute(t_cmd *list, t_shell *shell)
{
	if (!list)
		return ;
	if (list->next != NULL)
		execute_pipeline(list, shell);
	else
		execute_single(list, shell);
}
