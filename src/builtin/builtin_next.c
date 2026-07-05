/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:57:17 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/04 20:10:03 by ejones           ###   ########.fr       */
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
	return (1);
}

static int	export_process_arg(char *arg, t_shell *shell)
{
	int	len;

	len = len_name(arg);
	if (!is_valid_identifier(arg, len))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	if (ft_strchr(arg, '='))
	{
		if (is_in_env(shell->env, arg, len))
			set_env_value(shell->env, arg, NULL);
		else
			export_add(arg, shell);
	}
	else if (!is_in_env(shell->env, arg, len))
		export_add(arg, shell);
	return (1);
}

int	exec_export(char **args, t_shell *shell)
{
	int	j;
	int	ret;

	j = 0;
	if (!args[1])
	{
		while (shell->env[j])
			print_export_line(shell->env[j++]);
		return (1);
	}
	j = 1;
	ret = 1;
	while (args[j])
	{
		if (!export_process_arg(args[j], shell))
			ret = 0;
		j++;
	}
	return (ret);
}

int	exec_unset(char **args, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	if (!args[1])
		return (1);
	len = len_name(args[1]);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], args[1], len)
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			while (shell->env[i + 1])
			{
				shell->env[i] = shell->env[i + 1];
				i++;
			}
			shell->env[i] = NULL;
			return (1);
		}
		i++;
	}
	return (1);
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
	return (1);
}
