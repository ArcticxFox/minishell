/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:57:17 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/07 12:18:12 by leonpouet        ###   ########.fr       */
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
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	set_env_value(shell->env, "PWD=", getcwd(buffer, 4096));
	return (0);
}

int	unset_loop(char **args, t_shell *shell, int i)
{
	int	j;
	int	len;

	j = 0;
	len = len_name(args[i]);
	while (shell->env[j])
	{
		if (!ft_strncmp(shell->env[j], args[i], len)
			&& (shell->env[j][len] == '=' || shell->env[j][len] == '\0'))
		{
			free(shell->env[j]);
			while (shell->env[j + 1])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			shell->env[j] = NULL;
		}
		j++;
	}
	return (0);
}

int	exec_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[1])
		return (1);
	while (args[i])
	{
		unset_loop(args, shell, i);
		i++;
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
