/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:43:20 by leonpouet         #+#    #+#             */
/*   Updated: 2026/05/26 12:20:01 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

execute_single(t_cmd *list, t_shell *shell)
{

}

execute_pipeline(t_cmd *list, t_shell *shell)
{

}

int	execute_redir(t_cmd *list, t_shell *shell)

int	is_builtin(char *cmd)
{
	static t_builtin	builtin[8] = {
	{"pwd", NULL},
	{"echo", NULL},
	{"exit", NULL},
	{"env", NULL},
	{"cd", NULL},
	{"export", NULL},
	{"unset", NULL},
	{NULL, NULL}
	};
	int					i;

	i = 0;
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, ft_strlen(builtin[i].name) + 1))
			return (1);
		i++;
	}
	return (0);
}
