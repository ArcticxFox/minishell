/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:16:57 by ejones            #+#    #+#             */
/*   Updated: 2026/07/03 19:01:56 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	do_execve(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	int		err;

	path = get_path(cmd->cmd, shell);
	if (!path)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		ft_putstr_fd(": command not found\n", 2);
		child_exit(shell, 127);
	}
	execve(path, cmd->args, shell->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(path);
	err = errno;
	if (err == ENOENT)
		child_exit(shell, 127);
	else
		child_exit(shell, 126);
}

void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell)
{
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
		child_exit(shell, 1);
	if (is_builtin(cmd->cmd))
	{
		builtin(cmd->args, shell);
		child_exit(shell, 0);
	}
	do_execve(cmd, shell);
}

static void	pipeline_fork_loop(t_cmd *list, t_pipe_state *state,
	pid_t *pids, t_shell *shell)
{
	t_cmd	*current;
	int		i;

	current = list;
	i = 0;
	while (current)
	{
		state->index = i;
		pids[i] = fork();
		if (pids[i] == 0)
			child_pipe_setup(current, state, shell);
		current = current->next;
		i++;
	}
}

void	execute_pipeline(t_cmd *list, t_shell *shell)
{
	t_pipe_state	state;
	pid_t			*pids;
	int				i;

	state.n_cmds = count_cmds(list);
	state.pipes = create_pipes(state.n_cmds - 1);
	pids = malloc(sizeof(pid_t) * state.n_cmds);
	if (!state.pipes || !pids)
	{
		if (state.pipes)
			free_pipes(state.pipes, state.n_cmds - 1);
		free(pids);
		return ;
	}
	state.pids = pids;
	pipeline_fork_loop(list, &state, pids, shell);
	close_all_pipes(state.pipes, state.n_cmds - 1);
	i = 0;
	while (i < state.n_cmds)
		waitpid(pids[i++], NULL, 0);
	free_pipes(state.pipes, state.n_cmds - 1);
	free(pids);
}

void	execute(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (cmd->next != NULL)
		execute_pipeline(cmd, shell);
	else
	{
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
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_value_exit = WEXITSTATUS(status);
		else
			g_value_exit = 128 + WTERMSIG(status);
		ft_printf("exit = %d\n", g_value_exit);
	}
}
