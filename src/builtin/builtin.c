/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:12:25 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/29 14:33:23 by leonpouet        ###   ########.fr       */
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

	i = 1;
	(void)shell;
	if (args[1])
	{
		if (!ft_strncmp(args[1], "-n", 3))
			i++;
		while (args[i])
		{
			ft_printf("%s", args[i]);
			i++;
		}
		if (!ft_strncmp(args[1], "-n", 3))
			return (1);
	}
	ft_printf("\n");
	return (1);
}

static void	exit_numeric_err(char *arg, t_shell *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_value_exit = 2;
	shell->should_exit = 1;
}

int	exec_exit(char **args, t_shell *shell)
{
	ft_putendl_fd("exit", 1);
	if (!args[1])
	{
		shell->should_exit = 1;
		return (g_value_exit);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (!is_numeric(args[1]) || is_overflowed(args[1]))
	{
		exit_numeric_err(args[1], shell);
		return (2);
	}
	g_value_exit = (int)(unsigned char)ft_atoll(args[1]);
	shell->should_exit = 1;
	return (g_value_exit);
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
