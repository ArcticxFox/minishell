/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:12:25 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/26 18:38:23 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **args, t_shell *shell)
{
	char	buffer[4096];

	(void)args;
	(void)shell;
	if (getcwd(buffer, 4096) == NULL)
	{
		write (1, "Error\n", 6);
		return (0);
	}
	else
		ft_printf("Current working directory: %s\n", buffer);
	return (1);
}

int	exec_echo(char **args, t_shell *shell)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	(void)shell;
	if (args[1])
	{
		if (!ft_strncmp(args[1], "-n", 3))
			i++;
		while (args[i])
		{
			if (x == 1)
				ft_printf(" ");
			ft_printf("%s", args[i]);
			x = 1;
			i++;
		}
		if (!ft_strncmp(args[1], "-n", 3))
			return (1);
	}
	ft_printf("\n");
	return (1);
}

int	exec_exit(char **args, t_shell *shell)
{
	(void)args;
	(void)shell;
	shell->should_exit = 1;
	return (0);
}

int	builtin(char **args, t_shell *shell)
{
	static t_builtin	builtin[8] = {
	{"pwd", exec_pwd},
	{"echo", exec_echo},
	{"exit", exec_exit},
	{"env", exec_env},
	{"cd", exec_cd},
	{"export", exec_export},
	{"unset", exec_unset},
	{NULL, NULL}
	};
	int					i;

	i = 0;
	while (builtin[i].name)
	{
		if (!ft_strncmp(args[0], builtin[i].name, 7))
			builtin[i].f(args, shell);
		i++;
	}
	return (1);
}
