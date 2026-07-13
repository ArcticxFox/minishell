/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:12:25 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/13 20:45:40 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **args, t_shell *shell)
{
	char	buffer[4096];

	if (args[1])
	{
		ft_putendl_fd("minishell: pwd: options aren't supported", 2);
		return (1);
	}
	if (getcwd(buffer, 4096) == NULL)
	{
		write (2, "Error\n", 6);
		shell->exit_value = 1;
	}
	else
	{
		ft_printf("Current working directory: %s\n", buffer);
		shell->exit_value = 0;
	}
	return (shell->exit_value);
}

void	echo_write(char **args, int i)
{
	int	j;

	j = i + 1;
	write(1, args[i], ft_strlen(args[i]));
	while (args[j] && is_n(args[j]))
		j++;
	if (args[j])
		write(1, " ", 1);
}

int	exec_echo(char **args, t_shell *shell)
{
	int	i;
	int	no_newline;

	(void)shell;
	i = 1;
	no_newline = 0;
	if (!*args)
		return (1);
	while (args[i])
	{
		if (!is_n(args[i]))
		{
			echo_write(args, i);
		}
		else
			no_newline = 1;
		++i;
	}
	if (!no_newline)
		ft_printf("\n");
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
