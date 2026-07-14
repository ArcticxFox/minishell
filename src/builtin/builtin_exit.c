/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 19:07:01 by ejones            #+#    #+#             */
/*   Updated: 2026/07/14 14:00:00 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (shell->exit_value);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(2);
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
	if (!shell->current_cmd->next)
		shell->exit_value = (int)(unsigned char)ft_atoll(args[1]);
	return (shell->exit_value);
}
