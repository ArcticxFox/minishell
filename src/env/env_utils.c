/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:22:34 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/14 12:58:36 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**hard_code_env(t_shell *shell)
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
		name = ft_strjoin("PWD=", path);
		export_add(name, shell);
		free(name);
		name = ft_strjoin("OLDPWD=", path);
		export_add(name, shell);
		export_add("TERM=xterm-256color", shell);
	}
	env[2] = NULL;
	free(name);
	return (env);
}

void	copy_env(char **envp, t_shell *shell)
{
	int		i;
	char	**cpy;

	i = 0;
	if (!envp || !*envp)
	{
		hard_code_env(shell);
		return ;
	}
	while (envp[i])
		i++;
	cpy = ft_calloc(sizeof(char *), i + 1);
	if (!cpy)
		return ;
	i = 0;
	while (envp[i])
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
			return ;
		i++;
	}
	shell->env = cpy;
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
		if (!ft_strncmp(env[i], name, len_name(name)))
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
