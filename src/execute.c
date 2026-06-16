/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:16:57 by ejones            #+#    #+#             */
/*   Updated: 2026/06/16 08:26:01 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	execute_pipeline(t_cmd *list, t_shell *shell)
{
	t_pipe_state	state;
	pid_t			*pids;
	t_cmd			*cur;
	int				i;

	state.n_cmds = count_cmds(list);
	state.pipes = create_pipes(state.n_cmds - 1);
	pids = malloc(sizeof(pid_t) * state.n_cmds);
	if (!state.pipes || !pids)
		return ;
	cur = list;
	i = 0;
	while (cur)
	{
		state.index = i;
		pids[i] = fork();
		if (pids[i] == 0)
			child_pipe_setup(cur, &state, shell);
		cur = cur->next;
		i++;
	}
	close_all_pipes(state.pipes, state.n_cmds - 1);
	i = 0;
	while (i < state.n_cmds)
		waitpid(pids[i++], NULL, 0);
	free_pipes(state.pipes, state.n_cmds - 1);
	free(pids);
}

void	execute(t_cmd *list, t_shell *shell)
{
	bool	has_pipe;
	t_cmd	*current;

	has_pipe = false;
	current = list;
	while (current)
	{

	}
	if (has_pipe)
		execute_pipeline(list, shell);
	else
		execute_single(list, shell);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**cmd_args;
// 	char	*path;
// 	char	*str;
// 	t_shell shell;

// 	shell.env = copy_env(envp);
// 	(void)ac;
// 	(void)av;
// 	while(1)
// 	{
// 		str = readline("minishell> ");
// 		cmd_args = ft_split(str, ' ');
// 		if (!str || !ft_strncmp(str, "exit", 5))
// 		{
// 			free(cmd_args);
// 			return 0;
// 		}
// 		path = get_path(cmd_args[0], &shell);
// 		if (path && cmd_args)
// 			execute(cmd_args, &shell);
// 		free(str);
// 	}
// 	return (1);
// }
