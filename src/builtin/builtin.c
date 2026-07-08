/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:12:25 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/07 17:51:09 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(char **args, t_shell *shell)
{
	char	buffer[4096];

	(void)args;
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

int	exec_echo(char **args, t_shell *shell)
{
	t_args	*tmp;
	int		no_newline;

	(void)args;
	tmp = shell->current_cmd->args->next;
	no_newline = 0;
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (is_n(tmp->value))
			no_newline = 1;
		else if (!ft_strncmp(tmp->value, "$?", 3))
			ft_putnbr_fd(shell->exit_value, 1);
		else
			write(1, tmp->value, ft_strlen(tmp->value));
		if (tmp->next && tmp->espace == true && !is_n(tmp->value))
			write(1, " ", 1);
		tmp = tmp->next;
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
	shell->exit_value = 2;
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
	shell->should_exit = 1;
	shell->exit_value = (int)(unsigned char)ft_atoll(args[1]);
	return (shell->exit_value);
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
