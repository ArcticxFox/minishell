/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:12:25 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/05 18:14:52 by ejones           ###   ########.fr       */
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
		write (2, "Error\n", 6);
		g_value_exit = 1;
	}
	else
	{
		ft_printf("Current working directory: %s\n", buffer);
		g_value_exit = 0;
	}
	return (g_value_exit);
}

int	exec_echo(char **args, t_shell *shell)
{
	int	i;
	int	no_newline;

	(void)shell;
	i = 1;
	no_newline = 0;
	if (!args[i])
		return (1);
	while (args[i])
	{
		if (is_n(args[i]))
		{
			no_newline = 1;
			i++;
		}
		else
		{
			write(1, args[i], ft_strlen(args[i]));
			i++;
		}
	}
	if (!no_newline)
		ft_printf("\n");
	return (0);
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
		return (0);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
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
	int					value;
	int					i;

	i = 0;
	value = 0;
	while (builtin[i].name)
	{
		if (!ft_strncmp(args[0], builtin[i].name, 7))
		{
			value = builtin[i].f(args, shell);
			return (value);
		}
		i++;
	}
	return (1);
}
