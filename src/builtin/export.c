/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:16:28 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/07 15:05:52 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_append_val(char **env, t_args **arg, int len, int i)
{
	char	*val;
	char	*entry;

	if (env[i])
	{
		if ((*arg)->value[len + 2] == '\0' && (*arg)->espace == false
			&& (*arg)->next)
			val = ft_strjoin(&env[i][len + 1], (*arg)->next->value);
		else
			val = ft_strjoin(&env[i][len + 1], (*arg)->value + len + 2);
	}
	else if ((*arg)->value[len + 2] == '\0' && (*arg)->espace == false
		&& (*arg)->next)
		val = ft_strdup((*arg)->next->value);
	else
		val = ft_strdup((*arg)->value + len + 2);
	entry = ft_strjoin_free(ft_substr((*arg)->value, 0, len), "=");
	entry = ft_strjoin_free(entry, val);
	if ((*arg)->value[len + 2] == '\0' && (*arg)->espace == false
		&& (*arg)->next)
		(*arg) = (*arg)->next->next;
	else
		(*arg) = (*arg)->next;
	free(val);
	return (entry);
}

int	export_append(t_args **args, t_shell *shell)
{
	int		len;
	int		i;
	char	*entry;

	len = len_name((*args)->value);
	i = 0;
	while (shell->env[i] && (ft_strncmp(shell->env[i], (*args)->value, len)
			|| shell->env[i][len] != '='))
		i++;
	entry = build_append_val(shell->env, args, len, i);
	if (!entry)
		return (0);
	if (!shell->env[i])
	{
		i = export_add_append(entry, shell);
		free(entry);
		return (i);
	}
	free(shell->env[i]);
	shell->env[i] = entry;
	return (1);
}

void	put_env_value(char **env, t_args **args, int len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], (*args)->value, len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
		{
			free(env[i]);
			if ((*args)->value[len + 1] == '\0' && (*args)->espace == false
				&& (*args)->next)
			{
				env[i] = ft_strjoin((*args)->value, (*args)->next->value);
				(*args) = (*args)->next;
			}
			else
				env[i] = ft_strdup((*args)->value);
			(*args) = (*args)->next;
			return ;
		}
		i++;
	}
}

static int	export_process_arg(t_args **arg, t_shell *shell)
{
	int	len;

	len = len_name((*arg)->value);
	if (!is_valid_identifier((*arg)->value, len))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((*arg)->value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	if ((*arg)->value[len] == '+')
		return (export_append(arg, shell));
	if (ft_strchr((*arg)->value, '='))
	{
		if (is_in_env(shell->env, (*arg)->value, len))
			put_env_value(shell->env, arg, len);
		else
			export_add(arg, shell, len, true);
	}
	else if (!is_in_env(shell->env, (*arg)->value, len))
		export_add(arg, shell, len, false);
	return (1);
}

int	exec_export(char **args, t_shell *shell)
{
	t_args	*list_args;

	(void)args;
	list_args = shell->current_cmd->args->next;
	if (!list_args)
	{
		print_export_line(shell->env);
		return (1);
	}
	while (list_args)
	{
		if (!export_process_arg(&list_args, shell))
			return (0);
	}
	return (1);
}
