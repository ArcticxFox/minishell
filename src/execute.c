/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejones <ejones.42angouleme@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:16:57 by ejones            #+#    #+#             */
/*   Updated: 2026/04/15 17:17:20 by ejones           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static char	*ft_strjoin_free(char *s1, char const *s2)
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

char	*get_path(char *cmd)
{
	int		i = 0;
	char	*path;
	char	*mypath;
	char	**split = NULL;

	path = getenv("PATH");
	split = ft_split(path, ':');
	while(split[i])
	{
		mypath = ft_strjoin(split[i], "/");
		mypath = ft_strjoin_free(mypath, cmd);
		if (access(mypath, F_OK) == 0)
		{
			printf("%s\n", mypath);
			return (mypath);
		}
		free(mypath);
		i++;
	}
	printf("%s: command not found\n", cmd);
	return (NULL);
}

void	execute(char **args, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0) {
		// Child process
		execve(path, args, NULL);
		perror(path);
	}
	else {
		// Parent process
		waitpid(pid, NULL, 0);
		printf("Child finished\n");
	}
}

int	main(int ac, char **av)
{
	char	**cmd_args;
	char	*path;
	char	*str;


	(void)ac;
	(void)av;
	while(1)
	{
		str = readline("minishell> ");
		cmd_args = ft_split(str, ' ');
		if (!str || !ft_strncmp(str, "exit", 5))
			return 0;
		path = get_path(cmd_args[0]);
		if (path && cmd_args)
			execute(cmd_args, path);
	}
	return (1);
}
