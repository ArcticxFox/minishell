/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:16:57 by ejones            #+#    #+#             */
/*   Updated: 2026/07/05 19:24:45 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	nbr_args(t_args *lst)
{
	int	size;

	size = 0;
	if (lst != NULL)
	{
		size = 1;
		size += nbr_args(lst->next);
	}
	return (size);
}

char	**get_args_for_execve(t_args *args)
{
	int		n;
	int		i;
	char	**real_args;

	n = nbr_args(args);
	i = 0;
	real_args = malloc(sizeof(char *) * (n + 1));
	while (i < n && args)
	{
		real_args[i] = ft_strdup(args->value);
		if (!real_args[i])
		{
			free_memory(real_args);
			return (NULL);
		}
		++i;
		args = args->next;
	}
	real_args[i] = NULL;
	return (real_args);
}

static void	do_execve(t_cmd *cmd, t_shell *shell, char **real_args)
{
	char	*path;
	int		err;

	path = get_path(cmd->cmd, shell);
	if (!path)
	{
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		ft_putstr_fd(": command not found\n", 2);
		child_exit(shell, 127, real_args);
	}
	execve(path, real_args, shell->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	free(path);
	free_memory(real_args);
	err = errno;
	if (err == ENOENT)
		child_exit(shell, 127, NULL);
	else
		child_exit(shell, 126, NULL);
}

void	execute_child(t_cmd *cmd, int fd_in, int fd_out, t_shell *shell)
{
	char	**real_args;

	real_args = get_args_for_execve(cmd->args);
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
		child_exit(shell, 1, real_args);
	if (is_builtin(cmd->cmd))
	{
		g_value_exit = builtin(real_args, shell);
		child_exit(shell, 0, real_args);
	}
	if (cmd->cmd)
		do_execve(cmd, shell, real_args);
	else
		child_exit(shell, 0, real_args);
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

	state.n_cmds = count_cmds(list);
	state.pipes = create_pipes(state.n_cmds - 1);
	state.pids = malloc(sizeof(pid_t) * state.n_cmds);
	if (!state.pipes || !state.pids)
	{
		if (state.pipes)
			free_pipes(state.pipes, state.n_cmds - 1);
		free(state.pids);
		return ;
	}
	pipeline_fork_loop(list, &state, state.pids, shell);
	close_all_pipes(state.pipes, state.n_cmds - 1);
	exit_status(&state);
	free_pipes(state.pipes, state.n_cmds - 1);
	free(state.pids);
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
	}
}
