/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leonpouet <leonpouet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:16:57 by ejones            #+#    #+#             */
/*   Updated: 2026/06/02 16:21:42 by leonpouet        ###   ########.fr       */
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

char	*search_in_split(char **split, char *cmd)
{
	char	*mypath;
	int		i;

	i = 0;
	while(split[i])
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

	i = 0;
	path = get_env_value(shell->env, "PATH=");
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

int	execute(t_cmd *list, t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*cmd_node;

	current = list;
	while (current)
	{
		if (current->cmd[0] == '|')
			execute_pipeline(list, shell);
		current = current->next;
	}
	if (!current)
		execute_single(list, shell);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**cmd_args;
	char	*path;
	char	*str;
	t_shell shell;

	shell.env = copy_env(envp);
	(void)ac;
	(void)av;
	while(1)
	{
		str = readline("minishell> ");
		cmd_args = ft_split(str, ' ');
		if (!str || !ft_strncmp(str, "exit", 5))
		{
			free(cmd_args);
			return 0;
		}
		path = get_path(cmd_args[0], &shell);
		if (path && cmd_args)
			execute(cmd_args, &shell);
		free(str);
	}
	return (1);
}
