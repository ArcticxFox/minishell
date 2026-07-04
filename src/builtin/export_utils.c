/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 00:00:00 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/04 12:43:38 by leonpouet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *name, int len)
{
	int	i;

	if (!len)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (i < len)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
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

void	print_export_line(char *line)
{
	char	*res;

	res = ft_strchr(line, '=');
	if (res)
	{
		write(1, line, ft_strlen(res) - ft_strlen(line));
		ft_printf("='%s'\n", res + 1);
	}
	else
		ft_printf("%s=''\n", line);
}

int	export_add(char *arg, t_shell *shell)
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
