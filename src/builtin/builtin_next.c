/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:57:17 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/13 19:03:35 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char **args, t_shell *shell)
{
	char	buffer[4096];
	char	*path;

	if (!args[1])
	{
		path = get_env_value(shell->env, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = args[1];
	set_env_value(shell->env, "OLDPWD=", getcwd(buffer, 4096));
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd(' ', 2);
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	set_env_value(shell->env, "PWD=", getcwd(buffer, 4096));
	return (0);
}

void	remove_var(t_shell *shell, int *i)
{
	free(shell->env[*i]);
	while (shell->env[*i + 1])
	{
		shell->env[*i] = shell->env[*i + 1];
		++(*i);
	}
	shell->env[*i] = NULL;
}

int	exec_unset(char **args, t_shell *shell)
{
	int	i;
	int	n;
	int	len;

	i = 0;
	n = 1;
	if (!args[1])
		return (1);
	while (args[n])
	{
		len = len_name(args[n]);
		i = 0;
		while (shell->env[i])
		{
			if (!ft_strncmp(shell->env[i], args[n], len)
				&& (shell->env[i][len] == '=' || shell->env[i][len] == '\0'))
			{
				remove_var(shell, &i);
			}
			++i;
		}
		++n;
	}
	return (0);
}

int	exec_env(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	(void)args;
	while (shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			ft_printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
