/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:16:28 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/06 18:14:26 by ejones           ###   ########.fr       */
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
		i = export_add(entry, shell);
		free(entry);
		return (i);
	}
	free(shell->env[i]);
	shell->env[i] = entry;
	return (1);
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
	// if (ft_strchr(arg, '='))
	// {
	// 	if (is_in_env(shell->env, arg, len))
	// 		set_env_value(shell->env, arg, NULL);
	// 	else
	// 		export_add(arg, shell);
	// }
	// else if (!is_in_env(shell->env, arg, len))
	// 	export_add(arg, shell);
	return (1);
}

int	exec_export(char **args, t_shell *shell)
{
	int		j;
	int		ret;
	t_args	*list_args;

	j = 0;
	(void)args;
	list_args = shell->head->args->next;
	if (!list_args)
	{
		while (shell->env[j])
			print_export_line(shell->env[j++]);
		return (1);
	}
	j = 1;
	ret = 1;
	while (list_args)
	{
		if (!export_process_arg(&list_args, shell))
			ret = 0;
	}
	return (ret);
}
