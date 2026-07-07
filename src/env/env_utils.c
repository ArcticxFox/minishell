/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:22:34 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/07 18:16:52 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**hard_code_env(void)
{
	char	**env;
	char	buffer[4096];
	char	*path;
	char	*name;

	env = ft_calloc(sizeof(char *), 3);
	if (!env)
		return (NULL);
	path = getcwd(buffer, 4096);
	name = NULL;
	if (path)
	{
		ft_printf("%s\n", path);
		name = ft_strjoin("PWD=", path);
		set_env_value(env, name, NULL);
		free(name);
		name = ft_strjoin("OLDPWD=", path);
		set_env_value(env, name, NULL);
	}
	ft_printf("hello world\n", path);
	env[2] = NULL;
	free(name);
	return (env);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**cpy;

	i = 0;
	if (!envp || !*envp)
	{
		cpy = hard_code_env();
		return (cpy);
	}
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

char	*get_env_value(char **env, char *name)
{
	int	i;
	int	len;

	if (!env || !*env)
		return (NULL);
	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return (&env[i][len + 1]);
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
	while (args[i] && args[i] != '='
		&& !(args[i] == '+' && args[i + 1] == '='))
		i++;
	return (i);
}
