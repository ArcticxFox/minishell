/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:57:17 by leonpouet         #+#    #+#             */
/*   Updated: 2026/06/24 16:56:41 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cd(char **args, t_shell *shell)
{
	char	buffer[4096];

	if (!args[1])
		return (0);
	set_env_value(shell->env, "OLDPWD=", getcwd(buffer, 4096));
	if (chdir(args[1]) == -1)
	{
		write (2, "Error directory havn't change\n", 30);
		return (0);
	}
	set_env_value(shell->env, "PWD=", getcwd(buffer, 4096));
	return (1);
}

int	exec_export(char **args, t_shell *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	if (get_env_value(shell->env, args[1]))
		set_env_value(shell->env, args[1], NULL);
	else
	{
		while (shell->env[i])
			i++;
		tmp = malloc(sizeof(char *) * (i + 2));
		i = 0;
		while (shell->env[i])
		{
			tmp[i] = shell->env[i];
			i++;
		}
		tmp[i] = ft_strdup(args[1]);
		tmp[i + 1] = NULL;
		free(shell->env);
		shell->env = tmp;
	}
	return (1);
}

int	exec_unset(char **args, t_shell *shell)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (shell->env[i + 1])
	{
		if (!ft_strncmp(shell->env[i], args[1], len_name(args[1])))
		{
			free(shell->env[i]);
			f = 1;
		}
		if (f)
			shell->env[i] = shell->env[i + 1];
		i++;
	}
	shell->env[i] = shell->env[i + 1];
	return (1);
}
