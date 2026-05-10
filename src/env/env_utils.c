/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:22:34 by leonpouet         #+#    #+#             */
/*   Updated: 2026/05/10 19:29:07 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**cpy;

	i = 0;
	while (envp[i])
		i++;
	cpy = ft_calloc(sizeof(char *), i + 1);
	if (!cpy)
		return (0);
	i = 0;
	while (envp[i])
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
			return (0);
		i++;
	}
	return (cpy);
}

char	*get_env_value(char **env, char *name) // gestion erreur
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len_name(name) + 1))
			return (env[i] + len_name(name) + 1);
		i++;
	}
	return (NULL);
}

void	set_env_value(char **env, char *name, char *new_val)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len_name(name) + 1))
		{
			free(env[i]);
			if (new_val)
				env[i] = ft_strjoin(name, new_val);
			else
				env[i] = ft_strdup(name);
			return ;
		}
		i++;
	}
}

int	len_name(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '=' && args[i])
		i++;
	return (i);
}
