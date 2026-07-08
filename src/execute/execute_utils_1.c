/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:43:20 by leonpouet         #+#    #+#             */
/*   Updated: 2026/07/08 15:12:05 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	lenx;

	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	lenx = (len1 + ft_strlen(s2));
	s3 = (char *)ft_calloc((lenx + 1), sizeof(char));
	if (!s3)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(s3, s1, (len1 + 1));
		free(s1);
	}
	ft_strlcpy(&s3[len1], s2, ft_strlen(s2) + 1);
	return (s3);
}

int	count_cmds(t_cmd *cmds)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmds;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static char	*search_in_split(char **split, char *cmd)
{
	char	*mypath;
	int		i;

	i = 0;
	if (ft_strncmp(cmd, "..", 2) == 0)
		return (NULL);
	while (split[i])
	{
		mypath = ft_strjoin(split[i], "/");
		if (!mypath)
			return (NULL);
		mypath = ft_strjoin_free(mypath, cmd);
		if (!mypath)
			return (NULL);
		if (access(mypath, X_OK) == 0)
			return (mypath);
		free(mypath);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	*result;
	char	**split;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	i = 0;
	path = get_env_value(shell->env, "PATH");
	split = ft_split(path, ':');
	if (!split)
		return (NULL);
	result = search_in_split(split, cmd);
	while (split[i])
		free(split[i++]);
	free(split);
	if (!result)
		return (NULL);
	return (result);
}

int	is_builtin(char *cmd)
{
	static t_builtin	builtin[8] = {
	{"pwd", NULL},
	{"echo", NULL},
	{"exit", NULL},
	{"env", NULL},
	{"cd", NULL},
	{"export", NULL},
	{"unset", NULL},
	{NULL, NULL}
	};
	int					i;

	i = 0;
	if (!cmd)
		return (0);
	while (builtin[i].name)
	{
		if (!ft_strncmp(cmd, builtin[i].name, ft_strlen(builtin[i].name) + 1))
			return (1);
		i++;
	}
	return (0);
}
