/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:16:39 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/07 16:01:49 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *name, int len)
{
	int	i;

	if (!len)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_'
		&& name[0] != '\'' && name[0] != '"')
		return (0);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_'
			&& name[0] != '\'' && name[0] != '"')
			return (0);
		i++;
	}
	return (1);
}

int	is_in_env(char **env, char *name, int len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

void	print_export_line(char **env)
{
	int		j;
	char	*res;

	j = 0;
	while (env[j])
	{
		res = ft_strchr(env[j], '=');
		ft_printf("declare -x ");
		if (res)
		{
			write(1, env[j], res - env[j]);
			ft_printf("='%s'\n", res + 1);
		}
		else
			ft_printf("%s\n", env[j]);
		++j;
	}
}

int	export_add_append(char *arg, t_shell *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (0);
	i = 0;
	while (shell->env[i])
	{
		tmp[i] = shell->env[i];
		i++;
	}
	tmp[i] = ft_strdup(arg);
	if (!tmp[i])
	{
		free(tmp);
		return (0);
	}
	tmp[i + 1] = NULL;
	free(shell->env);
	shell->env = tmp;
	return (1);
}

char	*new_env_var(t_args **args, int len, bool equal)
{
	char	*tmp;

	if (equal == false && (*args)->value[len] == '\0'
		&& (*args)->espace == false && (*args)->next)
	{
		tmp = ft_strjoin((*args)->value, (*args)->next->value);
		*args = (*args)->next;
	}
	else if (equal == true && (*args)->value[len + 1] == '\0'
		&& (*args)->espace == false && (*args)->next)
	{
		tmp = ft_strjoin((*args)->value, (*args)->next->value);
		*args = (*args)->next;
	}
	else
		tmp = ft_strdup((*args)->value);
	*args = (*args)->next;
	return (tmp);
}

int	export_add(t_args **args, t_shell *shell, int len, bool equal)
{
	char	**tmp;
	int		i;

	i = 0;
	while (shell->env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (0);
	i = -1;
	while (shell->env[++i])
		tmp[i] = shell->env[i];
	tmp[i] = new_env_var(args, len, equal);
	if (!tmp[i])
	{
		free(tmp);
		return (0);
	}
	tmp[i + 1] = NULL;
	free(shell->env);
	shell->env = tmp;
	return (1);
}
