/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:16:28 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/05 14:22:45 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_append_val(char **env, char *arg, int len, int i)
{
	char	*val;
	char	*entry;

	if (env[i])
		val = ft_strjoin(&env[i][len + 1], arg + len + 2);
	else
		val = ft_strdup(arg + len + 2);
	entry = ft_strjoin_free(ft_substr(arg, 0, len), "=");
	entry = ft_strjoin_free(entry, val);
	free(val);
	return (entry);
}

int	export_append(char *arg, t_shell *shell)
{
	int		len;
	int		i;
	char	*entry;

	len = len_name(arg);
	i = 0;
	while (shell->env[i] && (ft_strncmp(shell->env[i], arg, len)
			|| shell->env[i][len] != '='))
		i++;
	entry = build_append_val(shell->env, arg, len, i);
	if (!entry)
		return (0);
	if (!shell->env[i])
	{
		i = export_add(entry, shell);
		free(entry);
		return (i);
	}
	free(shell->env[i]);
	shell->env[i] = entry;
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
	if (arg[len] == '+')
		return (export_append(arg, shell));
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
